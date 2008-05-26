/*
Open Asset Import Library (ASSIMP)
----------------------------------------------------------------------

Copyright (c) 2006-2008, ASSIMP Development Team
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

* Neither the name of the ASSIMP team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the ASSIMP Development Team.

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

/** @file Defines a post processing step to join identical vertices 
    on all imported meshes.*/
#ifndef AI_JOINVERTICESPROCESS_H_INC
#define AI_JOINVERTICESPROCESS_H_INC

#include "BaseProcess.h"
#include "../include/aiTypes.h"

struct aiMesh;

namespace Assimp
{

// ---------------------------------------------------------------------------
/** The JoinVerticesProcess unites identical vertices in all imported meshes. 
 * By default the importer returns meshes where each face addressed its own 
 * set of vertices even if that means that identical vertices are stored multiple
 * times. The JoinVerticesProcess finds these identical vertices and 
 * erases all but one of the copies. This usually reduces the number of vertices
 * in a mesh by a serious amount and is the standard form to render a mesh.
 */
class JoinVerticesProcess : public BaseProcess
{
	friend class Importer;

protected:
	/** Constructor to be privately used by Importer */
	JoinVerticesProcess();

	/** Destructor, private as well */
	~JoinVerticesProcess();

public:
	// -------------------------------------------------------------------
	/** Returns whether the processing step is present in the given flag field.
	 * @param pFlags The processing flags the importer was called with. A bitwise
	 *   combination of #aiPostProcessSteps.
	 * @return true if the process is present in this flag fields, false if not.
	*/
	bool IsActive( unsigned int pFlags) const;

	// -------------------------------------------------------------------
	/** Executes the post processing step on the given imported data.
	* At the moment a process is not supposed to fail.
	* @param pScene The imported data to work at.
	*/
	void Execute( aiScene* pScene);

protected:
	// -------------------------------------------------------------------
	/** Unites identical vertices in the given mesh.
	 * @param pMesh The mesh to process.
	 */
	bool ProcessMesh( aiMesh* pMesh);

	// -------------------------------------------------------------------
	/** Little helper function to calculate the quadratic difference 
	 * of two colours. 
	 * @param pColor1 First color
	 * @param pColor2 second color
	 * @return Quadratic color difference
	 */
	float GetColorDifference( const aiColor4D& pColor1, const aiColor4D& pColor2) const
	{
		aiColor4D c(	pColor1.r - pColor2.r, pColor1.g - pColor2.g, 
						pColor1.b - pColor2.b, pColor1.a - pColor2.a);
		return c.r*c.r + c.g*c.g + c.b*c.b + c.a*c.a;
	}
};

} // end of namespace Assimp

#endif // AI_CALCTANGENTSPROCESS_H_INC