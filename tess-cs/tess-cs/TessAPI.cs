using System;
using System.Runtime.InteropServices;
using System.Drawing;
using System.Text;


namespace tess_cs
{
    struct Constants
    {
        public const string dllName = "tesseract";
    }
    class TessAPI
    {
        #region Imported functions

        [DllImport(Constants.dllName, CallingConvention=CallingConvention.Cdecl, EntryPoint = "base_api_create")]
        public static extern IntPtr APICreate();

        [DllImport(Constants.dllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "api_end")]
        public static extern void APIEnd(IntPtr tess);

        [DllImport(Constants.dllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "api_init")]
        public static extern void APIInit(IntPtr tess, string lang = "eng");

        [DllImport(Constants.dllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "api_setup")]
        public static extern void APISetup(IntPtr tess, int settings);

        [DllImport(Constants.dllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "set_img_path")]
        public static extern int SetImgPath(IntPtr tess, string path);

        ///<summary>
        ///Sets the image to be processed from a byte stream
        ///</summary>
        ///<remarks>
        ///On windows, this will only read tiff formatted files from memory.
        ///For other formats, it requires fmemopen(3) (GNU).          
        ///Attempts to read those formats will fail at runtime.
        ///</remarks>
        [DllImport(Constants.dllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "set_img_array")]
        public static extern int SetImgArray(IntPtr tess, byte[] imageStream, int length, int page = 0);

        [DllImport(Constants.dllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "get_text")]
        public static extern int GetText(IntPtr tess, StringBuilder output, int offset, int length);

        [DllImport(Constants.dllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "get_text_length")]
        public static extern int GetTextLength(IntPtr tess, int includeNullChar = 1);

        [DllImport(Constants.dllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "tess_clear")]
        public static extern void TessClear(IntPtr tess);

        [DllImport(Constants.dllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "get_init_lang")]
        public static extern void GetInitLang(IntPtr tess, StringBuilder output);

        #endregion


        #region Helper functions

        public static string GetFullText(IntPtr tess) {
            int length = GetTextLength(tess);
            StringBuilder output = new StringBuilder(length);
            GetText(tess, output, 0, length);
            return output.ToString();
        }


        #endregion
    }
}
