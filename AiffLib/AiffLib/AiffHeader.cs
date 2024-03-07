using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AiffLib
{
    public class AiffHeader
    {
        //https://stackoverflow.com/questions/8704161/c-sharp-array-within-a-struct
        //char RIFF[4];        // RIFF Header      Magic header
        //unsigned long ChunkSize;      // RIFF Chunk Size  
        //char WAVE[4];        // WAVE Header      
        //char fmt[4];         // FMT header       
        //unsigned long Subchunk1Size;  // Size of the fmt chunk                                
        //unsigned short AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM 
        //unsigned short NumOfChan;      // Number of channels 1=Mono 2=Sterio                   
        //unsigned long SamplesPerSec;  // Sampling Frequency in Hz                             
        //unsigned long bytesPerSec;    // bytes per second 
        //unsigned short blockAlign;     // 1=8 bit mono, 2=16-bit mono, 4=16-bit stereo 
        //unsigned short bitsPerSample;  // Number of bits per sample      
        //char Subchunk2ID[4]; // "data"  string 
        //unsigned long Subchunk2Size;  // Sampled data length 

        //_wavHeader.RIFF			= gcnew array<System::Byte>{ 'R','I','F','F'};
        //_wavHeader.WAVE			= gcnew array<System::Byte>{ 'W','A','V','E'};
        //_wavHeader.fmt			= gcnew array<System::Byte>{ 'f','m','t',' '};
        //_wavHeader.Subchunk2ID	= gcnew array<System::Byte>{ 'd','a','t','a'};

        //_wavHeader.Subchunk1Size	= 16;	//16 for PCM
        //_wavHeader.AudioFormat		= 1;	//1  for PCM
        //_wavHeader.NumOfChan		= 1;
        //_wavHeader.SamplesPerSec	= 11025;
        //_wavHeader.bitsPerSample	= 16;
        //_wavHeader.blockAlign		= _wavHeader.NumOfChan* _wavHeader.bitsPerSample / 8;
        //_wavHeader.bytesPerSec	= _wavHeader.SamplesPerSec* _wavHeader.blockAlign;
        //_wavHeader.Subchunk2Size	= _numSamples* _wavHeader.blockAlign;
        //_wavHeader.ChunkSize		= 36 + _wavHeader.Subchunk2Size;

        //Note: 
        //Read Int32s as ReadInt32()
        //Read ushorts as ReadInt16();

        private char[] _RIFF;            //RIFF Header
        private Int32 _ChunkSize;        //RIFF Chunk Size
        private char[] _WAVE;            //WAVE Header
        private char[] _FMT;             //FMT Header
        private Int32 _Subchunk1Size;    // Size of the fmt chunk                                
        private Int16 _AudioFormat;     // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM 
        private Int16 _NumChan;         // Number of channels 1=Mono 2=Sterio                   
        private Int32 _SamplesPerSec;    // Sampling Frequency in Hz                             
        private Int32 _BytesPerSec;      // bytes per second 
        private Int16 _BlockAlign;      // 1=8 bit mono, 2=16-bit mono, 4=16-bit stereo 
        private Int16 _BitsPerSample;   // Number of bits per sample 
        private char[] _Subchunk2ID;     // "data"  string 
        private Int32 _Subchunk2Size;    // Sampled data length 

        private int _numBytesInHeader;

        private Int32 _numDataPoints;

        //private byte[] _fileBuffer;

        private byte[] _headerBuffer;

        private byte[] _dataBuffer;

        private string _filePath;

        //Some formulas
        //BytesPerSec = SamplesPerSec * NumChan * BitsPerSample/8
        //BlockAlign  = NumOfChan*BitsPerSample / 8;

        //set up to write 16 bit mono at 44100 samples per second
        //                                             RIFF        Chunk   WAVE       FMT       Sub    Audio   Samples  Bytes    Block     DATA       Sub
        //                                                         Size                         Chunk1 Fmr &   Per Sec  Per Sec  Align+               Chunk2         
        //                                                         36+                          size   Num                       Bits per             Size
        //                                                         nDataBytes                          Chans                     sample               nDataBytes
        private int[] _sixteenBitMono44100Template = { 0X46464952, 0x24, 0X45564157, 0X20746D66, 0x10, 0X10001, 0xAC44, 0x15888, 0X100002, 0X61746164, 0 };
        //The only fields you need to change in sixteenBitMono44100 is ChunkSize and SubChunk2Size; Chunksize is 36+num data bytes and SubChunk2Size is num data bytes.

        private enum MachineStates { INIT_STATE, D_STATE, DA_STATE, DAT_STATE, DATA_STATE };

        //Indices into editable elements of template arrays
        private enum TemplateIndex { RIFF = 0, CHUNKSIZE = 1, WAVE = 2, FMT = 3, SUBCHUNK1SIZE = 4, AUDIOFMT_NUMCHAN = 5, SAMP_PER_SEC = 6, BYTES_PER_SEC = 7, BLOCKALIGH_BITS_PER_SAMP = 8, DATA = 9, SUBCHUNK2SIZE = 10 };

        public AiffHeader()
        {
            _RIFF = new char[4];
            _WAVE = new char[4];
            _FMT = new char[4];
            _Subchunk2ID = new char[4];

            //_fileBuffer = null;
            _dataBuffer = null;
            _headerBuffer = null;
        }

        public Int32 ChunkSize
        {
            get { return _ChunkSize; }
            set { _ChunkSize = value; }
        }

        public Int32 Subchunk1Size
        {
            get { return _Subchunk1Size; }
            set { _Subchunk1Size = value; }
        }

        public Int16 AudioFormat
        {
            get { return _AudioFormat; }
            set { _AudioFormat = value; }
        }

        public Int16 NumChannels
        {
            get { return _NumChan; }
        }

        public Int32 SamplesPerSecond
        {
            get { return _SamplesPerSec; }
        }

        public Int16 BlockAlign
        {
            get { return _BlockAlign; }
            set { _BlockAlign = value; }
        }

        public Int16 BitsPerSample
        {
            get { return _BitsPerSample; }
            set { _BitsPerSample = value; }
        }

        public Int32 Subchunk2Size
        {
            get { return _Subchunk2Size; }
            set { _Subchunk2Size = value; }
        }

        public Int32 NumDataPoints
        {
            get { return _numDataPoints; }
        }

        public string FilePath
        {
            get { return _filePath; }
        }

        public int NumBytesInHeader
        {
            get { return _numBytesInHeader; }
        }

        //public byte[] FileBuffer
        //{
        //    get { return _fileBuffer; }
        //}

        public byte[] HeaderBuffer
        {
            get { return _headerBuffer; }
        }

        public byte[] DataBuffer
        {
            get { return _dataBuffer; }
        }


        public int[] SixteenBitMono44100Template
        {
            get
            {
                int[] cpy = new int[11];

                Array.Copy(_sixteenBitMono44100Template, cpy, _sixteenBitMono44100Template.Length);

                return cpy;
            }
        }

        //https://stackoverflow.com/questions/8704161/c-sharp-array-within-a-struct
        public byte[] ReadHeader(string filePath)
        {
            _filePath = filePath;

            try
            {
                int nRead = 0;

                using (System.IO.BinaryReader br = new System.IO.BinaryReader(System.IO.File.Open(filePath, System.IO.FileMode.Open)))
                {
                    _RIFF = br.ReadChars(4);
                    nRead += 4;

                    for (int i = 0; i < 4; i++)
                        Console.WriteLine(_RIFF[i].ToString());

                    _ChunkSize = (Int32)br.ReadInt32();

                    nRead += 4;

                    _WAVE = br.ReadChars(4);

                    nRead += 4;

                    for (int i = 0; i < 4; i++)
                        Console.WriteLine(_WAVE[i].ToString());

                    _FMT = br.ReadChars(4);

                    nRead += 4;

                    for (int i = 0; i < 4; i++)
                        Console.WriteLine(_FMT[i].ToString());

                    _Subchunk1Size = br.ReadInt32();

                    nRead += 4;

                    _AudioFormat = br.ReadInt16();

                    nRead += 2;

                    _NumChan = br.ReadInt16();

                    nRead += 2;

                    _SamplesPerSec = br.ReadInt32();

                    nRead += 4;

                    _BytesPerSec = br.ReadInt32();

                    nRead += 4;

                    _BlockAlign = br.ReadInt16();

                    nRead += 2;

                    _BitsPerSample = br.ReadInt16();

                    nRead += 2;

                    //This is supposed to be more robust
                    nRead += ReadSubchunk2ID(br, _Subchunk2ID);

                    //Subchunk2ID = br.ReadChars(4);
                    //nRead += 4;

                    for (int i = 0; i < 4; i++)
                        Console.WriteLine(_Subchunk2ID[i].ToString());

                    _Subchunk2Size = br.ReadInt32();

                    nRead += 4;

                    Console.WriteLine("ChunkSize {0} SubChunk1Size {1}  AudioFormat {2} NumChan {3}", _ChunkSize, _Subchunk1Size, _AudioFormat, _NumChan);
                    Console.WriteLine("SamplesPerSec {0} BytesPerSec {1} BlockAlign {2} BitsPerSample {3}", _SamplesPerSec, _BytesPerSec, _BlockAlign, _BitsPerSample);
                    Console.WriteLine("Subchunk2Size {0}", _Subchunk2Size);

                    _numBytesInHeader = nRead;

                    _numDataPoints = _Subchunk2Size / _BlockAlign;

                    //This is done in WavFile.cs now
                    //byteBuffer is big enough to hold header and data
                    //_fileBuffer = new byte[(Int32)_numBytesInHeader + _Subchunk2Size];

                    _headerBuffer = new byte[_numBytesInHeader];

                    //rewind the stream. read the header into the header buffer then copy to the fileBuffer
                    br.BaseStream.Seek(0, System.IO.SeekOrigin.Begin);

                    //Read into headerBuffer
                    br.Read(_headerBuffer, 0, _numBytesInHeader);

                    //This is done in WavFile.cs now
                    //Copy from headerBuffer to fileBuffer;
                    //Buffer.BlockCopy(_headerBuffer,0, _fileBuffer, 0, _headerBuffer.Length);

                    Console.WriteLine("Num Bytes In Header {0}", _numBytesInHeader);
                    Console.WriteLine("Num data points {0}", _numDataPoints);
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("Exception reading wav header {0}", e.Message);
            }

            return _headerBuffer;
        }

        private int ReadSubchunk2ID(System.IO.BinaryReader br, char[] Subchunk2ID)
        {

            //I have learned that we really do not know how many bytes
            //there are from bitsPerSample wav header member to
            //the Subchunk2ID. 
            //So we read 1 byte at a time until we read
            //the character sequence "data", which is Subchunk2ID
            //

            int nBytes = 0;

            MachineStates state = MachineStates.INIT_STATE;

            char ch;


            bool found = false;
            while (!found)
            {
                ch = br.ReadChar();

                nBytes++;

                switch (state)
                {
                    case MachineStates.INIT_STATE:
                        if (ch == 'd')
                        {
                            state = MachineStates.D_STATE;
                            Subchunk2ID[0] = ch;
                        }
                        break;
                    case MachineStates.D_STATE:
                        if (ch == 'a')
                        {
                            state = MachineStates.DA_STATE;
                            Subchunk2ID[1] = ch;
                        }
                        else if (ch == 'd')
                            state = MachineStates.D_STATE;
                        else
                            state = MachineStates.INIT_STATE;
                        break;
                    case MachineStates.DA_STATE:
                        if (ch == 't')
                        {
                            state = MachineStates.DAT_STATE;
                            Subchunk2ID[2] = ch;
                        }
                        else if (ch == 'd')
                            state = MachineStates.D_STATE;
                        else
                            state = MachineStates.INIT_STATE;
                        break;
                    case MachineStates.DAT_STATE:
                        if (ch == 'a')
                        {
                            Subchunk2ID[3] = ch;
                            found = true;
                        }
                        else if (ch == 'd')
                            state = MachineStates.D_STATE;
                        else
                            state = MachineStates.INIT_STATE;

                        break;
                    case MachineStates.DATA_STATE:
                        break;
                }
            }

            return nBytes;
        }

        public void WriteBlockAlignBitsPerSampleToTemplate(Int16 blockAlign, Int16 bitsPerSample, int[] hdrTemplate)
        {
            hdrTemplate[(int)TemplateIndex.BLOCKALIGH_BITS_PER_SAMP] = CombineTwoInt16(blockAlign, bitsPerSample);

            Console.WriteLine("Hex: {0:X}", hdrTemplate[(int)TemplateIndex.BLOCKALIGH_BITS_PER_SAMP]);

        }

        //Combine two Int16's into a Int32
        //https://stackoverflow.com/questions/28369693/c-sharp-join-2-int16-into-int32
        //First parameter in least significant position
        public int CombineTwoInt16(Int16 v1, Int16 v2)
        {
            Console.WriteLine("v1 {0} v2 {1}", v1, v2);

            int combined = v2 << 16 | v1;

            Console.WriteLine("Hex: {0:X}", combined);

            return combined;
        }
    }
}
