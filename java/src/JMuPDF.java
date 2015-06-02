import me.lumpchen.jmupdf.JMuLibrary;
import me.lumpchen.jmupdf.JMuLibrary.DocumentInfo;

import com.sun.jna.Pointer;

public class JMuPDF {

	private JMuLibrary library = JMuLibrary.INSTANCE;
	private Pointer ctx;
	private Pointer document;

	public JMuPDF() {
		this.ctx = this.library.j_mu_init_Context();
		this.library.j_mu_register_document_handlers(this.ctx);
	}

	public void open(String fileName) {
		this.document = this.library.j_mu_open_document(this.ctx, fileName);
	}

	public int getPageCount() {
		int n = this.library.j_mu_count_pages(this.ctx, this.document);
		return n;
	}
	
	public DocumentInfo getDocumentInfo() {
		DocumentInfo info = this.library.j_mu_get_doc_info(this.ctx, this.document);
		return info;
	}
}
