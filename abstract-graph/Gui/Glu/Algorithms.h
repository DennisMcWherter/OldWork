/**
 * Application: AbstractGraph
 * Module: GUI
 * File: Glu/Algorithms.h
 * Description: A list of algorithms
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id: Algorithms.h 112 2012-04-29 16:52:48Z Dennis.McWherter@gmail.com $
 */

#ifndef GLU_ALGORITHMS_H__
#define GLU_ALGORITHMS_H__

/**
 * Enum of supported algorithms
 */
enum ALGORITHMS
{
  SHORTESTPATH,
  MST,
  MAXMATCH,
  MAXNET,
  BIPARTITESETS,
  ODDCYLCE,
  EULER,
  IMPORTPRUFER,
  EXPORTPRUFER,
  SCC,
  GRAPHICSEQ,
  ALLPAIRS
};

#endif /* GLU_ALGORITHMS_H__ */
