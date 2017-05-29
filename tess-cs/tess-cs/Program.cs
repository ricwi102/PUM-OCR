using System;
using System.Text;



namespace tess_cs
{
 
    static class Program
    {
        static void Main(string[] args)
        {      
            Console.WriteLine("START! \nreferens:" +
                " \nO**: Ö" +                
                " \no**: ö" +
                " \nA**: Ä" +
                " \na**: ä" +
                " \nA*: Å" +
                " \na*: å");
            Console.ReadLine();

            string text = FromArray("./res/kvitto3.png");
            //string text = FromFile("./res/");   

            Console.WriteLine(text);         
            Console.ReadLine();        
        }        

        static string FromFile(string path) {
            IntPtr tess = TessAPI.APICreate();
            TessAPI.APISetup(tess, 1);
            TessAPI.APIInit(tess, "swe");

            TessAPI.SetImgPath(tess, path);

            string text = TessAPI.GetFullText(tess);
            TessAPI.APIEnd(tess);

            return text;
        }


        static string FromArray(string path) {
            IntPtr tess = TessAPI.APICreate();
            TessAPI.APISetup(tess, 1);
            TessAPI.APIInit(tess, "swe");
            
            byte[] imStream = ImageHandler.ImageToArray(@path);
            TessAPI.SetImgArray(tess, imStream, imStream.Length);            
            
            string text = TessAPI.GetFullText(tess);
            TessAPI.APIEnd(tess);

            return text;
        }

    }
}

