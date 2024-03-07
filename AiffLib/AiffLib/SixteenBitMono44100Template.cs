using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AiffLib
{
    public class SixteenBitMono44100Template : AiffHeaderTemplate
    {
        //Some formulas
        //BytesPerSec = SamplesPerSec * NumChan * BitsPerSample/8
        //BlockAlign  = NumOfChan*BitsPerSample / 8;

        //set up to write 16 bit mono at 44100 samples per second
        //                           RIFF        Chunk   WAVE       FMT       Sub     Audio   Samples  Bytes    Block     DATA       Sub
        //                                       Size                         Chunk1  Fmt &   Per Sec  Per Sec  Align+               Chunk2         
        //                                       36+                          size    Num                       Bits per             Size
        //                                       nDataBytes                           Chans                     sample               nDataBytes
        //protected Int32[] _template = { 0X46464952, 0x24, 0X45564157, 0X20746D66, 0x10, 0X10001, 0xAC44, 0x15888, 0X100002, 0X61746164, 0 };

        //protected enum TemplateIndex {RIFF = 0, CHUNKSIZE = 1, WAVE = 2, FMR = 3, SUBCHUNK1SIZE = 4, AUDIOFMT_AND_NUMCHANS = 5, SAMPLES_PER_SEC = 6, BYTES_PER_SEC = 7, BLOCKALIGN_AND_BITSPERSAMPLE = 8, DATA = 9, SUBCHUNK2SIZE = 10 };

        //protected Int32 _subchunk2Size;

        public SixteenBitMono44100Template(byte[] dataBuffer) : base(dataBuffer)
        {
            //Console.WriteLine("SixteenBitMono");
        }
    }
}
