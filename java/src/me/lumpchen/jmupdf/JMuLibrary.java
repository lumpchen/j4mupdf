package me.lumpchen.jmupdf;

import java.util.Arrays;
import java.util.List;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Pointer;
import com.sun.jna.Structure;

public interface JMuLibrary extends Library {

	public static JMuLibrary INSTANCE = (JMuLibrary) Native.loadLibrary("j4mupdf", JMuLibrary.class);

	public Pointer j_mu_init_Context();
	
	public void j_mu_register_document_handlers(Pointer ctx);
	
	public Pointer j_mu_open_document(Pointer ctx, String fileName);
	
	public int j_mu_count_pages(Pointer ctx, Pointer document);

	public DocumentInfo.ByValue j_mu_get_doc_info(Pointer ctx, Pointer document);
	
	public static class DocumentInfo extends Structure {
		public static class ByReference extends DocumentInfo implements Structure.ByReference {
		}

		public static class ByValue extends DocumentInfo implements Structure.ByValue {
		}
		
		public String creator;
		
		@Override
		protected List<String> getFieldOrder() {
			return Arrays.asList(new String[] { 
					"creator"
					});
		}
	}
}
