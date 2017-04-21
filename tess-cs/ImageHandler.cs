using System.Drawing;
using System.IO;

namespace tess_cs
{
    class ImageHandler
    {
        public static byte[] ImageToArray(string path)
        {
            Image image = Image.FromFile(path);
            MemoryStream ms = new MemoryStream();
            image.Save(ms, System.Drawing.Imaging.ImageFormat.Tiff);
            return ms.ToArray();
        }
    }
}
