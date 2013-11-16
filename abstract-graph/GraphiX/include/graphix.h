/**
 * Application: GraphiX Library
 * Module: Library
 * File: graphix.h
 * Description: Main include for graphix library
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id: graphix.h 106 2012-04-28 19:32:07Z Dennis.McWherter@gmail.com $
 */

#ifndef GRAPHIX_LIB_H__
#define GRAPHIX_LIB_H__

// Make sure we have proper library import/export type
#if _WIN32
#define GRAPHIX_PROD
#endif

#include "graphix_incl.h"

#include "Gfx/Circle.h"
#include "Gfx/Color.h"
#include "Gfx/Line.h"
#include "Gfx/Shape.h"

#include "Scene/Scene.h"

#include "Control/Mode.h"
#include "Control/NodeCreationMode.h"
#include "Control/EdgeCreationMode.h"
#include "Control/EditMode.h"

#endif /* GRAPHIX_LIB_H__ */

