
#ifndef _JMUPDF_H_
#define _JMUPDF_H_

extern "C" {
#include <mupdf/pdf.h>
}

#define J_MU_EXPORT(x) extern "C" __declspec(dllexport) x

struct DocumentInfo
{
	char* creator;
};

J_MU_EXPORT(fz_context*) j_mu_init_Context();

J_MU_EXPORT(void) j_mu_register_document_handlers(void*);

J_MU_EXPORT(pdf_document*) j_mu_open_document(void*, const char*);

J_MU_EXPORT(int) j_mu_count_pages(void*, void*);

J_MU_EXPORT(pdf_page*) j_mu_load_page(void*, void*, int);

J_MU_EXPORT(DocumentInfo) j_mu_get_doc_info(void*, void*);


#endif //_JMUPDF_H_