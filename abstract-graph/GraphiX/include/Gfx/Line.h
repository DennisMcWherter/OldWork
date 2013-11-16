/**
 * Application: GraphiX Library
 * Module: Library
 * File: Line.h
 * Description: Line interface
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id: Line.h 115 2012-04-29 22:07:43Z Dennis.McWherter@gmail.com $
 */

#ifndef GRAPHIX_GFX_LINE_H__
#define GRAPHIX_GFX_LINE_H__

#include "graphix_incl.h"
#include "Shape.h"
#include "Circle.h"

#include <utility>
#include <vector>

namespace GRAPHIX
{

/**
 * Curve types
 */
enum CURVE
{
  UP,
  DOWN,
  NONE
};

class GRAPHIX_EXPORT Line : public Shape
{
public:
  /**
   * Constructor
   *
   * @param cl    Circle one
   * @param cr    Circle two
   */
  Line(Circle* cl, Circle* cr);
  
  /**
   * Copy Constructor
   */
  Line(const Line& rhs);
  
  /**
   * Destructor
   */
  virtual ~Line();
  
  /**
   * Update the line width
   *
   * @param w   The new width of the line
   */
  virtual void setWidth(float w);
  
  /**
   * Update edge weight
   *
   * @param weight   The new weight (-1 to disable)
   */
  virtual void updateWeight(int weight);
  
  /**
   * Get the edge weight
   *
   * @return  The weight of the edge
   */
  virtual int getWeight() const;
  
  /**
   * Set directed
   *
   * @param set   If true, then directed line. False otherwise
   */
  virtual void setDirected(bool set);
  
  /**
   * Set the direction of the line
   *
   * @param right If true, the graph is directed to 
   *  the right. To the left otherwise.
   * NOTE: Only works IFF setDirected is true
   */
  virtual void setDirection(bool right);
  
  /**
   * Update the sides each circle is
   * on
   */
  virtual void updateCirclePositions();
  
  /**
   * Get left and right end points respectively
   *
   * @return  A pointer to left or right end point 
   */
  virtual Circle* getLeft() const;
  virtual Circle* getRight() const;
  virtual Circle* getTo() const;
  virtual Circle* getFrom() const;
  
  /**
   * Set curve type
   *
   * @param curve   Curve type
   */
  virtual void setCurve(CURVE curve);
  
  /**
   * Draw a line
   */
  virtual void draw() const;
  
  /**
   * Draw extra stuff (i.e. directed arrow, etc.)
   */
  virtual void drawExtra() const;
  
  /**
   * Return shape type
   */
  virtual SHAPES getType() const;
  
private:
  /**
   * Draw an arrow head
   *
   * @param size  The size of the arrow head
   * @return  Coordinate vector
   */
  std::vector<std::pair<float, float> > makeArrowHead(float size) const;
  
  /**
   * Normalize a pair
   *
   * @param p   The pair to normalize
   */
  static void normalize(std::pair<float, float>& p);
  
  Circle* cl, *cr, *to, *from;
  float width;
  bool directed, direction;
  int weight;
  CURVE curve;
};
}

#endif /* GRAPHIX_GFX_LINE_H__ */

