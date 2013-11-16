#ifndef __OBJECT_H
#define __OBJECT_H

#include <irrlicht.h>
#include <fstream>
#include <vector>
#include <string.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace std;
class Object
{
public:
	Object();
	~Object();

	// Sets
	inline void setPosition(vector3df position) { _node->setPosition(position); }
	inline void setRotation(vector3df position) { _node->setPosition(position); }
	inline void setNode(IAnimatedMeshSceneNode *node) { _node = node; }
	inline void setMesh(IAnimatedMesh *mesh) { _mesh = mesh; }
	inline void setMaterial(ITexture *texture) { 
		if(_node){
	_node->setMaterialFlag(EMF_LIGHTING, false);
		_node->setMaterialTexture( 0, texture); 
		}
		}

	// Gets
	inline vector3df position() const
	{ 
		if(_node == NULL)
			return vector3df();
		return _node->getPosition();
	}
	inline vector3df rotation() const
	{ 
		if(_node == NULL)
			return vector3df();
		return _node->getRotation();
	}
	inline IAnimatedMesh *mesh() { return _mesh; }
	
	



protected:
	IAnimatedMesh *_mesh;
	IAnimatedMeshSceneNode *_node;
};

#endif // __OBJECT_H
