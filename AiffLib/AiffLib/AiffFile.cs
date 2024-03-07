using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using NAudio.Wave;

namespace AiffLib
{
    public class AiffFile
    {
        private AiffHeader _aiffHdr;

        private byte[] _headerBuffer;
        private byte[] _dataBuffer;
        private byte[] _fileBuffer;

        private string _filePath;

        private AiffHeaderTemplate _hdrTemplate;

        ////set up to write 16 bit mono at 44100 samples per second
        //private int[] _sixteenBitMono44100Template = { 0X46464952, 0x24, 0X45564157, 0X20746D66, 0x10, 0X10001, 0xAC44, 0x15888, 0X100002, 0X61746164, 0 };

        //public int[] SixteenBitMono44100Template
        //{
        //    get
        //    {
        //        return _wavHdr.SixteenBitMono44100Template;
        //    }
        //}

        //Creating wav header for wav memory streams
        //https://stackoverflow.com/questions/22695723/create-valid-wav-file-header-for-streams-in-memory
        public AiffFile()
        {
            _aiffHdr = new AiffHeader();
        }

        //public WavFile(string filePath)
        //{
        //    _filePath = filePath;

        //    _wavHdr = new WavHeader();
        //}

        public AiffHeader AiffHeader
        {
            get { return _aiffHdr; }
            set { _aiffHdr = value; }
        }

        public byte[] FileBuffer
        {
            get { return _fileBuffer; }
        }

        public byte[] HeaderBuffer
        {
            get { return _aiffHdr.HeaderBuffer; }
        }

        public byte[] ByteDataBuffer
        {
            get { return _dataBuffer; }
        }

        public Int16[] IntDataBuffer
        {
            get
            {
                if (_dataBuffer == null)
                    return null;
                else
                {
                    Int16[] intBuffer = new Int16[_aiffHdr.NumDataPoints];
                    //Copy data from _dataBuffer to intBuffer
                    Buffer.BlockCopy(_dataBuffer, 0, intBuffer, 0, _dataBuffer.Length);
                    return intBuffer;
                }
            }
        }

        public double[] DoubleDataBuffer
        {
            get
            {
                if (_dataBuffer == null)
                    return null;
                else
                {
                    Int16[] intBuf = IntDataBuffer;

                    double sum = 0.0;

                    double max = Double.MinValue;
                    double min = Double.MaxValue;

                    double[] doubleBuffer = new double[intBuf.Length];

                    for (int i = 0; i < intBuf.Length; i++)
                    {
                        double val = (double)intBuf[i] / Int16.MaxValue;

                        doubleBuffer[i] = val;

                        sum += val;

                        if (val > max)
                            max = val;
                        if (val < min)
                            min = val;

                        //Console.WriteLine(val);

                    }

                    return doubleBuffer;
                }
            }
        }

        public static void ConvertAiffToWav(string aiffFile, string wavFile)
        {
            using (AiffFileReader reader = new AiffFileReader(aiffFile))
            {
                using (WaveFileWriter writer = new WaveFileWriter(wavFile, reader.WaveFormat))
                {
                    byte[] buffer = new byte[4096];
                    int bytesRead = 0;
                    do
                    {
                        bytesRead = reader.Read(buffer, 0, buffer.Length);
                        writer.Write(buffer, 0, bytesRead);
                    } while (bytesRead > 0);

                    writer.Close();
                }
            }
        }

        public void ReadHeaderAndData(string inputFilePath)
        {
            AiffFileReader aifReader = new AiffFileReader(inputFilePath);

            //_headerBuffer = ReadHeader(inputFilePath);
            //_dataBuffer = ReadData(inputFilePath);

            //Console.WriteLine("WavLib::ReadHeaderAndData()");

            //if (_headerBuffer != null && _dataBuffer != null)
            //{
            //    _fileBuffer = new byte[_headerBuffer.Length + _dataBuffer.Length];

            //    //Copy from headerBuffer to fileBuffer;
            //    Buffer.BlockCopy(_headerBuffer, 0, _fileBuffer, 0, _headerBuffer.Length);

            //    //Copy dataBuffer to fileBuffer
            //    Buffer.BlockCopy(_dataBuffer, 0, _fileBuffer, _headerBuffer.Length, _dataBuffer.Length);

            //    Console.WriteLine("WavLib::ReadHeaderAndData() was successful.");
            //}
        }

        public T[] ReadHeaderAndData<T>(string inputFilePath)
        {
            //T can be type byte or type Int16 only
            _headerBuffer = ReadHeader(inputFilePath);
            _dataBuffer = ReadData(inputFilePath);

            T[] tArray = new T[_aiffHdr.NumChannels * _aiffHdr.NumDataPoints];

            Buffer.BlockCopy(_dataBuffer, 0, tArray, 0, _dataBuffer.Length);

            return tArray;
        }

        public T[] GetDataBuf<T>(string inputFilePath)
        {
            if (_headerBuffer == null || _dataBuffer == null)
                return ReadHeaderAndData<T>(inputFilePath);

            else
            {
                T[] tArray = new T[_aiffHdr.NumChannels * _aiffHdr.NumDataPoints];

                Buffer.BlockCopy(_dataBuffer, 0, tArray, 0, _dataBuffer.Length);

                return tArray;
            }
        }

        public static byte[] ConvertTArrayToByteArray<T>(T[] tArray)
        {
            byte[] byteArray = new byte[System.Runtime.InteropServices.Marshal.SizeOf(typeof(T)) * tArray.Length];

            Buffer.BlockCopy(tArray, 0, byteArray, 0, byteArray.Length);

            return byteArray;
        }

        public static byte[] ConvertTArrayToByteArray<T>(T[] tArray, int sizeT)
        {
            //byte[] byteArray = new byte[System.Runtime.InteropServices.Marshal.SizeOf(typeof(T)) * tArray.Length];
            byte[] byteArray = new byte[sizeT * tArray.Length];

            Buffer.BlockCopy(tArray, 0, byteArray, 0, byteArray.Length);

            return byteArray;
        }

        public byte[] ReadHeader(string inputFilePath)
        {
            return _aiffHdr.ReadHeader(inputFilePath);
        }

        private byte[] ReadData(string inputFilePath)
        {

            if (_headerBuffer == null)
            {
                throw new Exception("WaveFile::ReadData():You must ReadHeader(fileName) before you can read the data.");
            }

            try
            {
                using (BinaryReader br = new BinaryReader(System.IO.File.Open(inputFilePath, System.IO.FileMode.Open)))
                {
                    //Read the data

                    //re-read the subchunk2size to make sure it matches the header read.
                    //do this by seeking to _numBytesInHeader - 4. 
                    br.BaseStream.Seek(_aiffHdr.NumBytesInHeader - 4, System.IO.SeekOrigin.Begin);

                    Int32 subchunk2size = br.ReadInt32();

                    if (subchunk2size != _aiffHdr.Subchunk2Size)
                        throw new Exception("WaveFile:::ReadData():Subchunk2Size's do not match in ReadHeader and ReadData.Abort reading wav file");

                    //Console.WriteLine("Subchunk2size check {0}", subchunk2size);

                    _dataBuffer = new byte[subchunk2size];

                    int numBytesRead = br.Read(_dataBuffer, 0, (int)subchunk2size);

                    //This is done in WavFile.cs now
                    //Copy dataBuffer to fileBuffer
                    //Buffer.BlockCopy(_dataBuffer, 0 , _fileBuffer, _numBytesInHeader, numBytesRead);

                    //Console.WriteLine("Wav file read is successful.\n");
                }
            }
            catch (Exception e)
            {
                throw new Exception(String.Format("WaveFile::ReadData(): Exception reading wav data {0}", e.Message));
            }

            return _dataBuffer;
        }

        public void WriteFile(string outputFilePath)
        {
            if (_headerBuffer == null || _dataBuffer == null)
            {
                throw new Exception("WavFile::WriteFile():headerBuffer and/or _dataBuffer is/are null. You must define these before you can write the file.");
            }

            try
            {
                using (System.IO.BinaryWriter bw = new System.IO.BinaryWriter(System.IO.File.Open(outputFilePath, System.IO.FileMode.Create)))
                {
                    ////Read the data

                    ////re-read the subchunk2size to make sure it matches the header read.
                    ////do this by seeking to _numBytesInHeader - 4. 
                    //bw.BaseStream.Seek(_wavHdr.NumBytesInHeader - 4, System.IO.SeekOrigin.Begin);

                    //Int32 subchunk2size = (Int32)br.ReadInt32();

                    //if (subchunk2size != _wavHdr.Subchunk2Size)
                    //    throw new Exception("Subchunk2Size's do not match in ReadHeader and ReadData.Abort reading wav file");

                    ////Console.WriteLine("Subchunk2size check {0}", subchunk2size);

                    //_dataBuffer = new byte[subchunk2size];

                    //int numBytesRead = br.Read(_dataBuffer, 0, (int)subchunk2size);

                    ////This is done in WavFile.cs now
                    ////Copy dataBuffer to fileBuffer
                    ////Buffer.BlockCopy(_dataBuffer, 0 , _fileBuffer, _numBytesInHeader, numBytesRead);

                    bw.Write(_headerBuffer);
                    bw.Write(_dataBuffer);

                    //Console.WriteLine("Wav file write for {0} is successful.\n",outputFilePath);
                }
            }
            catch (Exception e)
            {
                throw new Exception(String.Format("WavFile::WriteFile():Exception writing wav file: {0}", e.Message));
            }
        }

        public void WriteFile(string outputFilePath, byte[] headerBuf, byte[] dataBuf)
        {
            if (headerBuf == null || dataBuf == null)
            {
                throw new Exception("WavFile::WriteFile():headerBuffer and/or _dataBuffer is/are null. You must define these before you can write the file.");
            }

            try
            {
                using (System.IO.BinaryWriter bw = new System.IO.BinaryWriter(System.IO.File.Open(outputFilePath, System.IO.FileMode.Create)))
                {
                    bw.Write(headerBuf);
                    bw.Write(dataBuf);

                    //Console.WriteLine("Wav file write for {0} is successful.\n", outputFilePath);
                }
            }
            catch (Exception e)
            {
                throw new Exception(String.Format("WavFile::WriteFile():Exception writing wav file: {0}", e.Message));
            }
        }

        public void WriteFile(string outputFilePath, byte[] fileBuf)
        {
            if (fileBuf == null)
            {
                throw new Exception("WavFile::WriteFile():File buffer (fileBuf) is null.");
            }

            try
            {
                using (System.IO.BinaryWriter bw = new System.IO.BinaryWriter(System.IO.File.Open(outputFilePath, System.IO.FileMode.Create)))
                {
                    ////Read the data

                    ////re-read the subchunk2size to make sure it matches the header read.
                    ////do this by seeking to _numBytesInHeader - 4. 
                    //bw.BaseStream.Seek(_wavHdr.NumBytesInHeader - 4, System.IO.SeekOrigin.Begin);

                    //Int32 subchunk2size = (Int32)br.ReadInt32();

                    //if (subchunk2size != _wavHdr.Subchunk2Size)
                    //    throw new Exception("Subchunk2Size's do not match in ReadHeader and ReadData.Abort reading wav file");

                    ////Console.WriteLine("Subchunk2size check {0}", subchunk2size);

                    //_dataBuffer = new byte[subchunk2size];

                    //int numBytesRead = br.Read(_dataBuffer, 0, (int)subchunk2size);

                    ////This is done in WavFile.cs now
                    ////Copy dataBuffer to fileBuffer
                    ////Buffer.BlockCopy(_dataBuffer, 0 , _fileBuffer, _numBytesInHeader, numBytesRead);


                    bw.Write(fileBuf);

                    //Console.WriteLine("Wav file write for {0} is successful.\n", outputFilePath);
                }
            }
            catch (Exception e)
            {
                throw new Exception(String.Format("WavFile::WriteFile():Exception writing wav file: {0}", e.Message));
            }
        }

        public void WriteFile(string outputFilePath, AiffHeaderTemplate hdrTemplate)
        {
            if (hdrTemplate == null)
            {
                throw new Exception("WavFile::WriteFile():WavHeaderTemplate is null. You must define these before you can write the file.");
            }

            try
            {
                _hdrTemplate = hdrTemplate;
                _headerBuffer = hdrTemplate.WriteHeaderToBuffer();
                _dataBuffer = hdrTemplate.DataBuffer;

                using (System.IO.BinaryWriter bw = new System.IO.BinaryWriter(System.IO.File.Open(outputFilePath, System.IO.FileMode.Create)))
                {
                    bw.Write(_headerBuffer);
                    bw.Write(_dataBuffer);

                    //Console.WriteLine("Wav file write for {0} is successful.\n", outputFilePath);
                }
            }
            catch (Exception e)
            {
                throw new Exception(String.Format("WavFile::WriteFile():Exception writing wav file: {0}", e.Message));
            }
        }

        public int CombineTwoInt16(Int16 v1, Int16 v2)
        {
            return (_aiffHdr.CombineTwoInt16(v1, v2));
        }

        public void WriteHeader(Int16 blockAlign, Int16 bitsPerSample, int[] hdrTemplate)
        {
            _aiffHdr.WriteBlockAlignBitsPerSampleToTemplate(blockAlign, bitsPerSample, hdrTemplate);

        }

        public byte[] UseSixteenBitMono44100Template(byte[] dataBuffer)
        {
            Int32 subchunk2Size = dataBuffer.Length;

            _hdrTemplate = new SixteenBitMono44100Template(dataBuffer);

            _headerBuffer = _hdrTemplate.WriteHeaderToBuffer();

            _dataBuffer = dataBuffer;

            return _headerBuffer;
        }

        public byte[] UseHeaderTemplate(AiffHeaderTemplate hdrTemplate)
        {
            //Int32 subchunk2Size = dataBuffer.Length;

            _hdrTemplate = hdrTemplate;

            _headerBuffer = _hdrTemplate.WriteHeaderToBuffer();

            _dataBuffer = hdrTemplate.DataBuffer;

            return _headerBuffer;
        }

        public byte[] DoubleArrayToByteArray(double[] dataBuffer)
        {
            double max = Double.MinValue;
            double min = Double.MaxValue;

            for (int i = 0; i < dataBuffer.Length; i++)
            {
                double val = dataBuffer[i];

                if (val > max)
                    max = val;
                if (val < min)
                    min = val;
            }

            if (Math.Abs(min) > max)
                max = Math.Abs(min);

            Int16[] intBuf = new Int16[dataBuffer.Length];

            for (int i = 0; i < dataBuffer.Length; i++)
            {
                dataBuffer[i] /= max;

                intBuf[i] = (Int16)(dataBuffer[i] * Int16.MaxValue);
            }

            byte[] byteBuf = new byte[2 * intBuf.Length];

            Buffer.BlockCopy(intBuf, 0, byteBuf, 0, byteBuf.Length);

            return byteBuf;
        }

        public void TestWriteConsole()
        {
            Console.WriteLine("WavLib::TestWriteConsole()");
        }

        public void WriteOutputFile(string outputFile, double[] arrayToWrite, short bitsPerSample, Int32 samplesPerSecond)
        {

            int i;

            int numPts = arrayToWrite.Length;

            Utilities.NormalizeToOne(arrayToWrite);

            short bytesPerSample = (short)(bitsPerSample / 8);

            byte[] byteBuf = null;

            //convert corrArray from float to bytes
            if (bitsPerSample == 8)
            {
                byte[] tArray = new byte[numPts];

                for (i = 0; i < numPts; i++)
                {
                    //In both cases corrArray is normalized from -1 to 1

                    //This is how to convert floats to bytes 
                    //Bytes are postive. No negative numbers allowed.
                    double a = arrayToWrite[i];
                    //HOOCH_2018
                    //for byte data 1 maps to 255, -1 maps to 0;
                    tArray[i] = (byte)Math.Ceiling((1.0 + a) * 255 / 2.0);
                    //tArray[i] = (byte)(128 * (a + 1));
                }

                byteBuf = tArray;
            }
            else
            {
                Int16[] tArray = new Int16[numPts];

                //This is for converting 16 bit data which signed
                //corrArray has been normalized from -1 to 1
                //negative numbers allowed
                for (i = 0; i < numPts; i++)
                {
                    double a = arrayToWrite[i];
                    tArray[i] = (short)(a * Constants.Int16MaxValue);
                }

                byteBuf = AiffLib.AiffFile.ConvertTArrayToByteArray<Int16>(tArray);
            }

            //This will set Subchunk2Size and ChunkSize
            AiffLib.AiffHeaderTemplate hdrTemplate = new AiffLib.SixteenBitMono44100Template(byteBuf);

            //This will set bytesPerSec and samplePerSec
            hdrTemplate.SamplesPerSec = samplesPerSecond;// (Int32)(samplesPerSecond / delayIncrement);

            //This will set BitsPerSample and BlockAlign
            hdrTemplate.BitsPerSample = bitsPerSample;

            WriteFile(outputFile, hdrTemplate);
        }

        public void WriteOutputFile(string outputFile, float[] arrayToWrite, short bitsPerSample, Int32 samplesPerSecond)
        {

            int i;

            int numPts = arrayToWrite.Length;

            Utilities.NormalizeToOne(arrayToWrite);

            short bytesPerSample = (short)(bitsPerSample / 8);

            byte[] byteBuf = null;

            //convert corrArray from float to bytes
            if (bitsPerSample == 8)
            {
                byte[] tArray = new byte[numPts];

                for (i = 0; i < numPts; i++)
                {
                    //In both cases corrArray is normalized from -1 to 1

                    //This is how to convert floats to bytes 
                    //Bytes are postive. No negative numbers allowed.
                    float a = arrayToWrite[i];
                    //HOOCH_2018
                    //1 maps to 255 -1 maps to zero
                    tArray[i] = (byte)Math.Ceiling((1.0 + a) * 255 / 2.0);
                    //tArray[i] = (byte)(128*(a+1));
                }

                byteBuf = tArray;
            }
            else
            {
                Int16[] tArray = new Int16[numPts];

                //This is for converting 16 bit data which signed
                //corrArray has been normalized from -1 to 1
                //negative numbers allowed
                for (i = 0; i < numPts; i++)
                {
                    float a = arrayToWrite[i];
                    tArray[i] = (short)(a * Constants.Int16MaxValue);
                }

                byteBuf = AiffLib.AiffFile.ConvertTArrayToByteArray<Int16>(tArray);
            }

            //This will set Subchunk2Size and ChunkSize
            AiffLib.AiffHeaderTemplate hdrTemplate = new AiffLib.SixteenBitMono44100Template(byteBuf);

            //This will set bytesPerSec and samplePerSec
            hdrTemplate.SamplesPerSec = samplesPerSecond;// (Int32)(samplesPerSecond / delayIncrement);

            //This will set BitsPerSample and BlockAlign
            hdrTemplate.BitsPerSample = bitsPerSample;

            WriteFile(outputFile, hdrTemplate);
        }

        public void WriteOutputAsTwoChannelWavFile(string outputFile, float[] chan1Array, float[] chan2Array, short bitsPerSample, Int32 samplesPerSecond)
        {

            int i;
            int j = 0;

            int bytesPerSample = (short)(bitsPerSample / 8);

            int numChan1Pts = chan1Array.Length;
            int numChan2Pts = chan2Array.Length;

            Utilities.NormalizeToOne(chan1Array);
            Utilities.NormalizeToOne(chan2Array);

            byte[] byteBuf = null;

            bool chan1LongestArray = false;

            int numPtsInLongestChannel = numChan2Pts;

            //Find the longest array
            if (numChan1Pts > numChan2Pts)
            {
                numPtsInLongestChannel = numChan1Pts;
                chan1LongestArray = true;
            }

            //will pad the shortest channel with zeros.
            int numChannelDataPts = 2 * numPtsInLongestChannel;

            //convert correlation from float to byte
            if (bitsPerSample == 8)
            {
                byte[] chan1Bytes = new byte[numChan1Pts];
                for (i = 0; i < numChan1Pts; i++)
                {
                    float a = chan1Array[i];
                    //HOOCH_2018
                    //1 maps to 255 -1 maps to zero
                    chan1Bytes[i] = (byte)Math.Ceiling((1.0 + a) * 255 / 2.0);
                    //chan1Bytes[i] = (byte)(128 * (a + 1));
                }

                byte[] chan2Bytes = new byte[numChan2Pts];

                j = 0;
                for (i = 0; i < numChan2Pts; i++)
                {
                    float a = chan2Array[i];
                    //HOOCH_2018
                    //1 -> 255, -1->0
                    chan2Bytes[j++] = (byte)Math.Ceiling((1.0 + a) * 255 / 2.0);
                    //chan2Bytes[i] = (byte)(128 * (a + 1));
                }

                byte[] channelData = new byte[numChannelDataPts];

                if (chan1LongestArray)
                {
                    j = 0;
                    for (i = 0; i < numChannelDataPts; i += 2)
                    {
                        channelData[i] = chan1Bytes[j];

                        if (j < numChan2Pts)
                            channelData[i + 1] = chan2Bytes[j];
                        else
                            channelData[i + 1] = 0;
                        j++;
                    }
                }
                else
                {
                    //channel 2 has longest array
                    j = 0;
                    for (i = 0; i < numChannelDataPts; i += 2)
                    {
                        if (j < numChan1Pts)
                            channelData[i] = chan1Bytes[j];
                        else
                            channelData[i] = 0;

                        channelData[i + 1] = chan2Bytes[j];

                        j++;
                    }
                }

                byteBuf = channelData;
                //This works for byte data but do not need it for byte data.
                //byteBuf = WavLib.WavFile.ConvertTArrayToByteArray<byte>(channelData);//, sizeof(byte));
            }
            else
            {
                Int16[] chan1Bytes = new Int16[numChan1Pts];
                for (i = 0; i < numChan1Pts; i++)
                {
                    //http://jfk-records.com/sensimetrics/berkovitz.htm
                    float a = chan1Array[i];
                    chan1Bytes[i] = (Int16)(a * Constants.Int16MaxValue);
                }

                Int16[] chan2Bytes = new Int16[numChan2Pts];

                for (i = 0; i < numChan2Pts; i++)
                {
                    //http://jfk-records.com/sensimetrics/berkovitz.htm
                    float a = chan2Array[i];
                    chan2Bytes[j++] = (Int16)(a * Constants.Int16MaxValue);
                }

                Int16[] channelData = new Int16[numChannelDataPts];

                if (chan1LongestArray)
                {
                    j = 0;
                    for (i = 0; i < numChannelDataPts; i += 2)
                    {
                        channelData[i] = chan1Bytes[j];

                        if (j < numChan2Pts)
                            channelData[i + 1] = chan2Bytes[j];
                        else
                            channelData[i + 1] = 0;
                        j++;
                    }
                }
                else
                {
                    //channel 2 has longest array
                    j = 0;
                    for (i = 0; i < numChannelDataPts; i += 2)
                    {
                        if (j < numChan1Pts)
                            channelData[i] = chan1Bytes[j];
                        else
                            channelData[i] = 0;

                        channelData[i + 1] = chan2Bytes[j];

                        j++;
                    }
                }

                byteBuf = AiffLib.AiffFile.ConvertTArrayToByteArray<Int16>(channelData);

            }

            //This will set Subchunk2Size and ChunkSize
            AiffLib.AiffHeaderTemplate hdrTemplate = new AiffLib.SixteenBitStereo44100Template(byteBuf);

            //This will set bytesPerSec and samplePerSec
            hdrTemplate.SamplesPerSec = samplesPerSecond;

            //This will set BitsPerSample and BlockAlign
            hdrTemplate.BitsPerSample = (short)bitsPerSample;

            WriteFile(outputFile, hdrTemplate);

        }

        public void WriteOutputFile(string outputFile, float[,] arrayToWrite, short bitsPerSample, Int32 sampsPerSecond)
        {
            int i;

            short bytesPerSample = (short)(bitsPerSample / 8);

            //want the length of the first dimension
            int numPts = arrayToWrite.GetLength(0);

            byte[] byteBuf = null;

            if (bitsPerSample == 8)
            {
                byte[] tArray = new byte[numPts];
                for (i = 0; i < numPts; i++)
                {
                    float a = arrayToWrite[i, 0];
                    //HOOCH_2018
                    //1 maps to 255 -1 maps to zero
                    tArray[i] = (byte)Math.Ceiling((1.0f + a) * 255 / 2.0f);
                    //tArray[i] = (byte)(128 * (a + 1));
                }

                byteBuf = tArray;
            }
            else
            {
                Int16[] tArray = new Int16[numPts];
                for (i = 0; i < numPts; i++)
                {
                    tArray[i] = (short)(arrayToWrite[i, 0] * Constants.Int16MaxValue);
                }

                byteBuf = AiffLib.AiffFile.ConvertTArrayToByteArray<Int16>(tArray);
            }

            //This will set Subchunk2Size and ChunkSize
            AiffLib.AiffHeaderTemplate hdrTemplate = new AiffLib.SixteenBitMono44100Template(byteBuf);

            //This will set bytesPerSec and samplePerSec
            hdrTemplate.SamplesPerSec = sampsPerSecond;

            //This will set BitsPerSample and BlockAlign
            hdrTemplate.BitsPerSample = bitsPerSample;

            WriteFile(outputFile, hdrTemplate);
        }

        public void WriteOutputAsTwoChannelWavFile(string outputFile, float[,] arrayToWrite, short bitsPerSample, Int32 sampsPerSecond)
        {
            int i, j;

            int bytesPerSample = (short)(bitsPerSample / 8);

            byte[] byteBuf = null;

            //want the length of the first dimension of the two dimensional array.
            int numPts = arrayToWrite.GetLength(0);

            //used for testing
            //Random rand = new Random();

            if (bitsPerSample == 8)
            {
                byte[,] tArray = new byte[numPts, 2];
                for (i = 0; i < numPts; i++)
                {
                    float a = arrayToWrite[i, 0];
                    //HOOCH_2018
                    //1 maps to 255 , -1 maps to zero
                    tArray[i, 0] = (byte)Math.Ceiling((1.0f + a) * 255 / 2.0f);
                    //tArray[i, 0] = (byte)(128 * (a + 1));

                    float b = arrayToWrite[i, 1];// rand.Next(0, 127);
                    tArray[i, 1] = (byte)b;
                }

                byte[] channelData = new byte[2 * numPts];

                j = 0;
                for (i = 0; i < 2 * numPts; i += 2)
                {
                    channelData[i] = tArray[j, 0];
                    channelData[i + 1] = tArray[j++, 1];
                }

                byteBuf = channelData;// WavLib.WavFile.ConvertTArrayToByteArray<byte>(channelData);
            }
            else
            {
                Int16[,] tArray = new Int16[numPts, 2];
                for (i = 0; i < numPts; i++)
                {
                    float a = arrayToWrite[i, 0];
                    tArray[i, 0] = (short)(a * Constants.Int16MaxValue);

                    float b = arrayToWrite[i, 1];// rand.Next(0, 32000);
                    tArray[i, 1] = (Int16)b;
                }

                Int16[] channelData = new Int16[2 * numPts];

                //track in channel 1 and correlation in channel 2
                j = 0;
                for (i = 0; i < 2 * numPts; i += 2)
                {
                    channelData[i] = tArray[j, 0];
                    channelData[i + 1] = tArray[j++, 1];
                }

                byteBuf = AiffLib.AiffFile.ConvertTArrayToByteArray<Int16>(channelData);
            }

            //This will set Subchunk2Size and ChunkSize
            AiffLib.AiffHeaderTemplate hdrTemplate = new AiffLib.SixteenBitStereo44100Template(byteBuf);

            //This will set bytesPerSec and samplePerSec
            hdrTemplate.SamplesPerSec = (Int32)sampsPerSecond;

            //This will set BitsPerSample and BlockAlign
            hdrTemplate.BitsPerSample = (short)(8 * bytesPerSample);

            WriteFile(outputFile, hdrTemplate);

        }
    }
}
