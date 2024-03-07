using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace AiffLib
{
    public class AiffHeaderTemplate
    {
        //Some formulas
        //BytesPerSec = SamplesPerSec * NumChan * BitsPerSample/8
        //BlockAlign  = NumOfChan*BitsPerSample / 8;
        //BlockAlign;     // 1=8 bit mono, 2=16-bit mono, 4=16-bit stereo 
        //AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM 

        //set up to write 16 bit mono at 44100 samples per second
        //                           RIFF        Chunk   WAVE       FMT       Sub     Audio   Samples  Bytes    Block     DATA       Sub
        //                                       Size                         Chunk1  Fmt &   Per Sec  Per Sec  Align+               Chunk2         
        //                                       36+                          size    Num                       Bits per             Size
        //                                       nDataBytes                           Chans                     sample               nDataBytes
        //This is the template for SixteenBitMono44100
        protected Int32[] _template = { 0X46464952, 0x24, 0X45564157, 0X20746D66, 0x10, 0X10001, 0xAC44, 0x15888, 0X100002, 0X61746164, 0 };

        protected enum TemplateIndex { RIFF = 0, CHUNKSIZE = 1, WAVE = 2, FMR = 3, SUBCHUNK1SIZE = 4, AUDIOFMT_AND_NUMCHANS = 5, SAMPLES_PER_SEC = 6, BYTES_PER_SEC = 7, BLOCKALIGN_AND_BITSPERSAMPLE = 8, DATA = 9, SUBCHUNK2SIZE = 10 };

        protected Int32 _subchunk2Size;

        protected byte[] _buffer;

        protected Int16 _numChan = 1;

        protected Int16 _bitsPerSample = 16;

        protected Int16 _audioFormat = 1; // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM 

        protected Int16 _blockAlign = 2; // 1=8 bit mono, 2=16-bit mono, 4=16-bit stereo 

        protected Int32 _samplesPerSec = 44100;

        protected Int32 _bytesPerSec = 0x15888;

        protected byte[] _dataBuffer;

        public AiffHeaderTemplate(byte[] dataBuffer)
        {
            Subchunk2Size = dataBuffer.Length;

            _dataBuffer = dataBuffer;

            Console.WriteLine("WavHeaderTemplate");
        }

        public Int32 Subchunk2Size
        {
            get { return _subchunk2Size; }
            set
            {
                _subchunk2Size = value;
                _template[(int)TemplateIndex.CHUNKSIZE] = 36 + value;
                _template[(int)TemplateIndex.SUBCHUNK2SIZE] = value;
            }
        }

        public byte[] Buffer
        {
            get { return _buffer; }
        }

        public byte[] DataBuffer
        {
            get { return _dataBuffer; }
        }

        public Int16 AudioFormat
        {
            set
            {
                _audioFormat = value;
                Int32 result = CombineTwoInt16(_audioFormat, _numChan);
                AudioFmtAndNumChan = result;
            }
        }

        public Int16 NumChan
        {
            set
            {
                _numChan = value;

                BlockAlign = (Int16)(value * _bitsPerSample / 8);

                Int32 result = CombineTwoInt16(_blockAlign, _bitsPerSample);

                BlockAlignAndBitsPerSample = result;

                result = CombineTwoInt16(_audioFormat, _numChan);

                AudioFmtAndNumChan = result;
            }
        }

        public Int16 BitsPerSample
        {
            set
            {
                _bitsPerSample = value;

                BlockAlign = (Int16)(_numChan * value / 8);

                Int32 result = CombineTwoInt16(_blockAlign, _bitsPerSample);

                BlockAlignAndBitsPerSample = result;
            }
        }

        public Int32 SamplesPerSec
        {
            set
            {
                _samplesPerSec = value;
                _template[(int)TemplateIndex.SAMPLES_PER_SEC] = value;

                BytesPerSec = value * _blockAlign;
            }
        }

        protected Int16 BlockAlign
        {
            set
            {
                _blockAlign = value;

                BytesPerSec = _samplesPerSec * value;
            }
        }

        protected Int32 AudioFmtAndNumChan
        {
            set
            {
                _template[(int)TemplateIndex.AUDIOFMT_AND_NUMCHANS] = value;
            }
        }

        protected Int32 BytesPerSec
        {
            set
            {
                _bytesPerSec = value;
                _template[(int)TemplateIndex.BYTES_PER_SEC] = value;
            }
        }

        protected Int32 BlockAlignAndBitsPerSample
        {
            set
            {
                _template[(int)TemplateIndex.BLOCKALIGN_AND_BITSPERSAMPLE] = value;
            }
        }

        public byte[] WriteHeaderToBuffer()
        {
            if (_subchunk2Size == 0)
                throw new Exception("WavHeaderTemplate::WriteHeaderToBuffer():Must set SubChunk2Size before you can write the header.");
            else
            {
                try
                {
                    using (MemoryStream ms = new MemoryStream(44))
                    {
                        using (BinaryWriter bw = new BinaryWriter(ms))
                        {
                            //Write the header
                            Array.ForEach(Enumerable.Range(0, _template.Length).ToArray(), i => bw.Write(_template[i]));
                        }

                        _buffer = ms.ToArray();
                    }
                }
                catch (Exception e)
                {
                    throw new Exception(String.Format("WavHeaderTemplate::WriteHeaderToBuffer(): Exception: ", e.Message));
                }
            }

            return _buffer;
        }

        //Combine two Int16's into a Int32
        //https://stackoverflow.com/questions/28369693/c-sharp-join-2-int16-into-int32
        //First parameter in least significant position
        public Int32 CombineTwoInt16(Int16 v1, Int16 v2)
        {
            //Console.WriteLine("v1 {0} v2 {1}", v1, v2);

            Int32 combined = v2 << 16 | v1;

            //Console.WriteLine("Hex: {0:X}", combined);

            return combined;
        }
    }
}
