/*
Open Asset Import Library (assimp)
----------------------------------------------------------------------

Copyright (c) 2006-2014, assimp team
All rights reserved.

Redistribution and use of this software in source and binary forms,
with or without modification, are permitted provided that the
following conditions are met:

* Redistributions of source code must retain the above
copyright notice, this list of conditions and the
following disclaimer.

* Redistributions in binary form must reproduce the above
copyright notice, this list of conditions and the
following disclaimer in the documentation and/or other
materials provided with the distribution.

* Neither the name of the assimp team, nor the names of its
contributors may be used to endorse or promote products
derived from this software without specific prior
written permission of the assimp team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------
*/
#ifndef ASSIMP_BUILD_NO_OPEMGEX_IMPORTER

#include "AssimpPCH.h"
#include "OpenGEXImporter.h"
#include "OpenGEXParser.h"
#include "DefaultIOSystem.h"

#include <vector>

static const aiImporterDesc desc = {
    "Open Game Engine Exchange",
    "",
    "",
    "",
    aiImporterFlags_SupportTextFlavour,
    0,
    0,
    0,
    0,
    "ogex"
};

namespace Assimp {
namespace OpenGEX {

//------------------------------------------------------------------------------------------------
OpenGEXImporter::OpenGEXImporter() {

}

//------------------------------------------------------------------------------------------------
OpenGEXImporter::~OpenGEXImporter() {

}

//------------------------------------------------------------------------------------------------
bool OpenGEXImporter::CanRead( const std::string &file, IOSystem *pIOHandler, bool checkSig ) const {
    bool canRead( false );
    if( !checkSig ) {
        canRead = SimpleExtensionCheck( file, "ogex" );
    } else {
        static const char *token[] = { "Metric", "GeometryNode", "VertexArray (attrib", "IndexArray" };
        canRead = BaseImporter::SearchFileHeaderForToken( pIOHandler, file, token, 4 );
    }

    return canRead;
}

//------------------------------------------------------------------------------------------------
void OpenGEXImporter::InternReadFile( const std::string &filename, aiScene *pScene, IOSystem *pIOHandler ) {
    // open source file
    IOStream *file = pIOHandler->Open( filename, "rb" );
    if( !file ) {
        throw DeadlyImportError( "Failed to open file " + filename );
    }

    std::vector<char> buffer;
    TextFileToBuffer( file, buffer );
    OpenGEXParser myParser( buffer );
    myParser.parse();
}

//------------------------------------------------------------------------------------------------
const aiImporterDesc *OpenGEXImporter::GetInfo() const {
    return &desc;
}

//------------------------------------------------------------------------------------------------
void OpenGEXImporter::SetupProperties( const Importer *pImp ) {

}

//------------------------------------------------------------------------------------------------

} // Namespace OpenGEX
} // Namespace Assimp

#endif // ASSIMP_BUILD_NO_OPEMGEX_IMPORTER
