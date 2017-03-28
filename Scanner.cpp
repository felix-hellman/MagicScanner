#include "Scanner.hpp"

Scanner::Scanner(string filename)
{
  ifstream inFile;
  inFile.open(filename.c_str(), ios::in|ios::binary|ios::ate);
  inFile.seekg(0,ios::end);
  this->fileSize = inFile.tellg();
  cout << "Size of file: " << fileSize << endl;
  inFile.seekg(0, ios::beg);
  this->fileBuffer = new char[fileSize];
  inFile.read(fileBuffer,fileSize);
  inFile.close();
  this->filterTAR = true;
  this->scan();
}
Scanner::~Scanner()
{
  delete[] fileBuffer;
}
void Scanner::scan()
{
  for(auto i = 0; i < fileSize; i++)
	{

		switch((unsigned char)fileBuffer[i])
		{
      case 0x25:
      if(i + 3 < fileSize)
        if(fileBuffer[i+1] == 0x50 && fileBuffer[i+2] == 0x44 && fileBuffer[i+3] == 0x46)
          printMagic("PDF");
      break;
			case 0x50:
      //PNG CASE
			if(i + 2  < fileSize)
				if(fileBuffer[i+1] == 0x4e && fileBuffer[i+2] == 0x47)
					printMagic("PNG");
      //ZIP CASE
      if(i+3 < fileSize)
        if(fileBuffer[i+1] == 0x4B && fileBuffer[i+2] < 0x09 && fileBuffer[i+3] < 0x09)
          if(fileBuffer[i+2] > 0x03 && fileBuffer[i+3] > 0x04)
            printMagic("ZIP");
			break;
      case 0x52:
      if(i + 5)
        if(fileBuffer[i+1] == 0x61 && fileBuffer[i+2] == 0x72 && fileBuffer[i+3] == 0x21 && fileBuffer[i+4] == 0x1A && fileBuffer[i+5] == 0x07)
          printMagic("RAR");
      break;
			case 0x1F:
			if(i + 3 < fileSize)
				if((unsigned char)fileBuffer[i+1] == 0x8B && fileBuffer[i+2] < 0x09 && fileBuffer[i+3] < 0x09)
            if(!this->filterTAR)
              printMagic("TAR.GZ");
			break;
      case 0x37:
      if(i + 5)
        if((unsigned char)fileBuffer[i+1] == 0x7A && (unsigned char)fileBuffer[i+2] == 0xBC && (unsigned char)fileBuffer[i+3] == 0xAF && (unsigned char)fileBuffer[i+4] == 0x27 && (unsigned char)fileBuffer[i+5] == 0x1C)
          printMagic("7Zip");
      case 0x7F:
      if(i+3 < fileSize)
        if((unsigned char)fileBuffer[i+1] == 0x45 && (unsigned char)fileBuffer[i+2] == 0x4C && (unsigned char)fileBuffer[i+3] == 0x46)
          printMagic("ELF");
      break;
      case 0xFF:
      if(i + 4 < fileSize)
        if((unsigned char)fileBuffer[i+1] == 0xD8 && (unsigned char)fileBuffer[i+2] == 0xFF && ((unsigned char)fileBuffer[i+3] == 0xDB || (unsigned char)fileBuffer[i+3] == 0xE0 || (unsigned char)fileBuffer[i+3] == 0xE1 ))
          printMagic("JPG / JPEG");
      break;
		}
	}
}
void Scanner::printMagic(string signature)
{
  cout << "Magic number found :\t\t" << signature << endl;
}
