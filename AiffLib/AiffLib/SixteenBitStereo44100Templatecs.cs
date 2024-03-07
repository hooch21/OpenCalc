using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AiffLib
{
    public class SixteenBitStereo44100Template : AiffHeaderTemplate
    {

        //Some formulas
        //BytesPerSec = SamplesPerSec * NumChan * BitsPerSample/8
        //BlockAlign  = NumOfChan*BitsPerSample / 8;

        //set up to write 16 bit mono at 44100 samples per second
        //                           RIFF        Chunk   WAVE       FMT       Sub     Audio   Samples  Bytes    Block     DATA       Sub
        //                                       Size                         Chunk1  Fmt &   Per Sec  Per Sec  Align+               Chunk2         
        //                                       36+                          size    Num                       Bits per             Size
        //                                       nDataBytes                           Chans                     sample               nDataBytes
        //private Int32[] _template = { 0X46464952, 0x24, 0X45564157, 0X20746D66, 0x10, 0X20001, 0xAC44, 0x2B110, 0X100004, 0X61746164, 0 };


        public SixteenBitStereo44100Template(byte[] dataBuffer) : base(dataBuffer)
        {
            NumChan = 2;
            //Console.WriteLine("SixteenBitStereo");
        }
    }
}
