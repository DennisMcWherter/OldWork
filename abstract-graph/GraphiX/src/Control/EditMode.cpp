/**
 * Application: GraphiX Library
 * Module: Library
 * File: EditMode.h
 * Description: Edit mode - can move nodes but no node/edge creation
 * 
 * @author Dennis J. McWherter, Jr.
 * @version $Id: EditMode.cpp 106 2012-04-28 19:32:07Z Dennis.McWherter@gmail.com $
 */

#include "Control/EditMode.h"

namespace GRAPHIX
{
EditMode::EditMode(std::vector<Shape*>* shapes, std::vector<Shape*>* selected, const Color& highlight)
  : Mode(shapes, selected, highlight)
{
}

EditMode::~EditMode()
{
}

MODES EditMode::getMode() const
{
  return EDIT;
}
}