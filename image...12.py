	
import sys
import hashlib
 
def main():
    print "Enter the name of original image"
    orig = raw_input()
    print "Enter the name of image you want to check for tampering "
    new = raw_input()
    image_file1 =open(orig).read()
    image_file2 =open(new).read()
    x=hashlib.md5(image_file1).hexdigest()
    print x
    y=hashlib.md5(image_file2).hexdigest()
    print y
    if x==y:
        print "Image not tampered"
    else:
        print "!!!!!!!!Image tampered!!!!!!!"
 
main()
sys.exit(0);
