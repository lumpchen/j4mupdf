import me.lumpchen.jmupdf.JMuLibrary.DocumentInfo;

public class Test {

	public static void main(String[] args) {
		JMuPDF mupdf = new JMuPDF();
		
		mupdf.open("c:/2312.pdf");
		int n = mupdf.getPageCount();
		System.out.println(n);
		
		DocumentInfo info = mupdf.getDocumentInfo();
		if (info != null) {
			System.out.println(info.creator);	
		}
	}
}
