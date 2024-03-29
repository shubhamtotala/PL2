
/*ASSIGNMENT NO.:14 (B)		
TITLE:Write a program to Implement a fingerprint recognition using Java Programming
BATCH:T2*/

import java.awt.Image;
import java.awt.Toolkit;
import java.awt.image.PixelGrabber;
public class Compare {
static void processImage() {
String file1 = "p4.jpg";
String file2 = "p6.jpg";
Image image1 = Toolkit.getDefaultToolkit().getImage(file1);
Image image2 = Toolkit.getDefaultToolkit().getImage(file2);
try {
PixelGrabber grab1 =new PixelGrabber(image1, 0, 0, -1, -1, false);
PixelGrabber grab2 =new PixelGrabber(image2, 0, 0, -1, -1, false);
int[] data1 = null;
if (grab1.grabPixels()) {
int width = grab1.getWidth();
int height = grab1.getHeight();
data1 = new int[width * height];
data1 = (int[]) grab1.getPixels();
}
int[] data2 = null;
if (grab2.grabPixels()) {
int width = grab2.getWidth();
int height = grab2.getHeight();
data2 = new int[width * height];
data2 = (int[]) grab2.getPixels();
}
System.out.println("Fingerprint matches : " + java.util.Arrays.equals(data1, data2));
} catch (InterruptedException e1) {
e1.printStackTrace();
}
}
public static void main(String args[]) {
processImage();
}
}



/*comp-sl-19@compsl19-OptiPlex-3020:~$ javac Compare.java
comp-sl-19@compsl19-OptiPlex-3020:~$ java Compare
Fingerprint matches : true
comp-sl-19@compsl19-OptiPlex-3020:~$ 



IMAGES ARE:-
  

 
           

 
     






 
comp-sl-19@compsl19-OptiPlex-3020:~$ javac Compare.java
comp-sl-19@compsl19-OptiPlex-3020:~$ java Compare
Fingerprint matches : false
comp-sl-19@compsl19-OptiPlex-3020:~$ 



IMAGES ARE:-

  
 
 
*/





