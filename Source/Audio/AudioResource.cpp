#include "stdafx.h"

#include "AudioResource.h"
#include <portaudio.h>
#include <sndfile.h>
#include <assert.h>
#include <iostream>

typedef int DWORD;

#define RIFF 0x46464952
#define WAVE 0x45564157
#define FACT 0x74636166
#define FMT_ 0x20746D66
#define DATA 0x61746164

std::string SoundExtraData::VToString()
{
	return "Sound File";
}

int WaveResourceLoader::VBufferLength(char *rawBuffer, int bufferLength)
{
		DWORD           file = 0; 
        DWORD           fileEnd = 0; 
        
        DWORD           length = 0;     
        DWORD           type = 0;                                                                       

        DWORD pos = 0;

        // The first 4 bytes of a valid .wav file is 'R','I','F','F'
        type = *((DWORD *)(rawBuffer+pos));             pos+=sizeof(DWORD);
        if(type != RIFF) // "RIFF" in hexadecimal form. backwards because little endian
		{
			return false;   
		}

        length = *((DWORD *)(rawBuffer+pos));   pos+=sizeof(DWORD);
        type = *((DWORD *)(rawBuffer+pos));             pos+=sizeof(DWORD);

        // 'W','A','V','E' for a legal .wav file
		if(type !=  WAVE){ // "WAVE" in hex
			return false;           //not a WAV
		}
        // Find the end of the file
        fileEnd = length - 4;
        
        bool copiedBuffer = false;

        // Load the .wav format and the .wav data
        // Note that these blocks can be in either order.
        while(file < fileEnd)
        {
                type = *((DWORD *)(rawBuffer+pos));             pos+=sizeof(DWORD);
                file += sizeof(DWORD);

                length = *((DWORD *)(rawBuffer+pos));   pos+=sizeof(DWORD);
                file += sizeof(DWORD);

                switch(type)
                {
                        case FACT: //"fact"
                        {
                                assert(false && "This wav file is compressed.  We don't handle compressed wav at this time");
                                break;
                        }

                        case FMT_: //"fmt "
                        {
                                pos+=length;   
                                break;
                        }

                        case DATA: //"data"
                        {
                                return length;
                        }
                } 

                file += length;

                // Increment the pointer past the block we just read,
                // and make sure the pointer is word aligned.
                if (length & 1)
                {
                        ++pos;
                        ++file;
                }
        } 

        // If we get to here, the .wav file didn't contain all the right pieces.
        return false; 
}

bool WaveResourceLoader::VLoadResource(char *rawBuffer, int bufferLength, ResHandle* handle)
{
	std::shared_ptr<SoundExtraData> extra(new SoundExtraData());

	DWORD           file = 0; 
    DWORD           fileEnd = 0; 
        
    DWORD           length = 0;     
    DWORD           type = 0;                                                                       

    DWORD pos = 0;

	// The first 4 bytes of a valid .wav file is 'R','I','F','F'
    type = *((DWORD *)(rawBuffer+pos));             pos+=sizeof(DWORD);
    if(type != RIFF) // "RIFF" in hexadecimal form. backwards because little endian
	{
		return false;   
	}

    length = *((DWORD *)(rawBuffer+pos));   pos+=sizeof(DWORD);
    type = *((DWORD *)(rawBuffer+pos));             pos+=sizeof(DWORD);

	// 'W','A','V','E' for a legal .wav file
	if(type !=  WAVE)
	{
		return false;           //not a WAV
	}

	// Find the end of the file
    fileEnd = length - 4;
        
    bool copiedBuffer = false;
	

	// Load the .wav format and the .wav data
    // Note that these blocks can be in either order.
    while(file < fileEnd)
    {
            type = *((DWORD *)(rawBuffer+pos));             pos+=sizeof(DWORD);
            file += sizeof(DWORD);

            length = *((DWORD *)(rawBuffer+pos));   pos+=sizeof(DWORD);
            file += sizeof(DWORD);

            switch(type)
                {
                    case FACT: //"fact"
                    {
                            assert(false && "This wav file is compressed.  We don't handle compressed wav at this time");
                            break;
                    }

                    case FMT_: //"fmt "
                    {
                            pos+=length;   
                            break;
                    }

                    case DATA: //"data"
                    {
						//We got to the data portion, now we need to copy it into the handle's buffer
                        memcpy(handle->m_buffer, rawBuffer + pos, length);
						copiedBuffer = true;
						break;
                    }
            } 

            file += length;

			if (copiedBuffer)
			{
				extra->m_lengthMilli = handle->getSize() * 1000 / 44100;
				handle->setExtra(extra);
			}

            // Increment the pointer past the block we just read,
            // and make sure the pointer is word aligned.
            if (length & 1)
            {
                    ++pos;
                    ++file;
            }
    } 

	return false;
}

char* WaveResourceLoader::VGetFileExtension()
{
	return "wav";
}