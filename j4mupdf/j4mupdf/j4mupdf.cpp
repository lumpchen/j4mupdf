// j4mupdf.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "j4mupdf.h"

fz_context* j_mu_init_Context()
{
	fz_context* ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);
	return ctx;
}

void j_mu_register_document_handlers(void* p_ctx)
{
	fz_context* ctx = (fz_context*) p_ctx;
	fz_register_document_handlers(ctx);
}

pdf_document* j_mu_open_document(void* p_ctx, const char* filename)
{
	fz_context* ctx = (fz_context*)p_ctx;
	pdf_document* doc = pdf_open_document(ctx, filename);
	return doc;
}

int j_mu_count_pages(void* p_ctx, void* p_doc)
{
	fz_context* ctx = (fz_context*) p_ctx;
	pdf_document* doc = (pdf_document*) p_doc;
	int n = pdf_count_pages(ctx, doc);
	return n;
}

pdf_page* j_mu_load_page(void* p_ctx, void* p_doc, int number)
{
	fz_context* ctx = (fz_context*) p_ctx;
	pdf_document* doc = (pdf_document*) p_doc;
	pdf_page* page = pdf_load_page(ctx, doc, number);
	return page;
}

// some PDF documents contain control characters in outline titles or /Info properties
static wchar_t *pdf_clean_string(wchar_t *string)
{
	for (wchar_t *c = string; *c; c++) {
		if (*c < 0x20 && *c != '\n' && *c != '\r' && *c != '\t')
			*c = ' ';
	}
	return string;
}

template <typename T>
inline T *AllocArray(size_t n)
{
	return (T*)calloc(n, sizeof(T));
}

static wchar_t *get_prop_str(fz_context* ctx, pdf_obj *obj, const char *name)
{
	pdf_obj* p_obj = pdf_dict_getp(ctx, obj, name);

	int len = pdf_to_str_len(ctx, p_obj) + 1;

	wchar_t *buf = AllocArray<wchar_t>(len);
	pdf_to_ucs2_buf(ctx, (unsigned short *)buf, p_obj);

	return p_obj ? pdf_clean_string(buf) : nullptr;
}

DocumentInfo j_mu_get_doc_info(void* p_ctx, void* p_doc)
{
	fz_context* ctx = (fz_context*) p_ctx;
	pdf_document* doc = (pdf_document*)p_doc;
	pdf_obj* info = pdf_dict_gets(ctx, pdf_trailer(ctx, doc), "Info");

	DocumentInfo doc_info;
	if (info)
	{
		doc_info.author = get_prop_str(ctx, info, "Author");
		doc_info.creator = get_prop_str(ctx, info, "Creator");
		doc_info.creation_date = get_prop_str(ctx, info, "CreationDate");
		doc_info.producer = get_prop_str(ctx, info, "Producer");
		doc_info.title = get_prop_str(ctx, info, "Title");
	}
	return doc_info;
}

void j_mu_render_page(void* p_ctx, void* p_page)
{
	fz_context* ctx = (fz_context*) p_ctx;
	pdf_page* page = (pdf_page*)p_page;

	fz_matrix transform;
	fz_rotate(&transform, 0);

	fz_pre_scale(&transform, 100 / 100.0f, 100 / 100.0f);
	fz_rect bounds;
	pdf_bound_page(ctx, page, &bounds);
	fz_transform_rect(&bounds, &transform);

	fz_irect bbox;
	fz_round_rect(&bbox, &bounds);
	fz_pixmap *pix = fz_new_pixmap_with_bbox(ctx, fz_device_rgb(ctx), &bbox);
	fz_pixmap_set_resolution(pix, 300);
	fz_clear_pixmap_with_value(ctx, pix, 0xff);
}

