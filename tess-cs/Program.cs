using System;
using System.Text;



namespace tess_cs
{
 
    static class Program
    {
        static void Main(string[] args)
        {      
            Console.WriteLine("SUP!");
            Console.ReadLine();

            string text = FromArray("D:/Programmering/PUM-OCR/tess-cs/res/ocr-test.jpg");
            //string text = FromFile("D:/Programmering/PUM-OCR/tess-cs/res/phototest.tif");      

            Console.WriteLine(text);         
            Console.ReadLine();        
        }        

        static string FromFile(string path) {
            IntPtr tess = TessAPI.APICreate();
            TessAPI.APIInit(tess, "swe");
            TessAPI.APISetup(tess);
            

            TessAPI.SetImgPath(tess, path);

            string text = TessAPI.GetFullText(tess);
            TessAPI.APIEnd(tess);

            return text;
        }


        static string FromArray(string path) {
            IntPtr tess = TessAPI.APICreate();
            TessAPI.APIInit(tess, "swe");
            TessAPI.APISetup(tess);

            
            byte[] imStream = ImageHandler.ImageToArray(@path);
            TessAPI.SetImgArray(tess, imStream, imStream.Length);            
            
            string text = TessAPI.GetFullText(tess);
            TessAPI.APIEnd(tess);

            return text;
        }

    }
}

