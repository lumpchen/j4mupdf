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

DocumentInfo j_mu_get_doc_info(void* p_ctx, void* p_doc)
{
	fz_context* ctx = (fz_context*) p_ctx;
	pdf_document* doc = (pdf_document*)p_doc;
	pdf_obj* info = pdf_dict_gets(ctx, pdf_trailer(ctx, doc), "Info");

	//if (!info)
	//{
		//return NULL;
	//}
	DocumentInfo doc_info;
	pdf_obj* creator = pdf_dict_getp(ctx, info, "Creator");
	if (creator)
	{
		doc_info.creator = pdf_to_str_buf(ctx, creator);
	}

	return doc_info;
}