/*=========================================================================

Program:   VMTK
Module:    $RCSfile: vtkvmtkRecursiveGaussianImageFilter.h,v $
Language:  C++
Date:      $Date: 2006/04/06 16:48:25 $
Version:   $Revision: 1.2 $

  Copyright (c) Luca Antiga, David Steinman. All rights reserved.
  See LICENCE file for details.

  Portions of this code are covered under the VTK copyright.
  See VTKCopyright.txt or http://www.kitware.com/VTKCopyright.htm 
  for details.

  Portions of this code are covered under the ITK copyright.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm
  for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

// .NAME vtkvmtkRecursiveGaussianImageFilter - Wrapper class around itk::RecursiveGaussianImageFilter
// .SECTION Description
// vtkvmtkImageFilter


#ifndef __vtkvmtkRecursiveGaussianImageFilter_h
#define __vtkvmtkRecursiveGaussianImageFilter_h


#include "vtkSimpleImageToImageFilter.h"
#include "vtkvmtkWin32Header.h"

class VTK_VMTK_SEGMENTATION_EXPORT vtkvmtkRecursiveGaussianImageFilter : public vtkSimpleImageToImageFilter
{
 public:
  static vtkvmtkRecursiveGaussianImageFilter *New();
  vtkTypeRevisionMacro(vtkvmtkRecursiveGaussianImageFilter,vtkSimpleImageToImageFilter);

  vtkSetMacro(Sigma,double);
  vtkGetMacro(Sigma,double);

  vtkSetMacro(NormalizeAcrossScale,int);
  vtkGetMacro(NormalizeAcrossScale,int);
  vtkBooleanMacro(NormalizeAcrossScale,int);

protected:
  vtkvmtkRecursiveGaussianImageFilter();
  ~vtkvmtkRecursiveGaussianImageFilter() {};
  
  void SimpleExecute(vtkImageData *input, vtkImageData *output);

private:
  vtkvmtkRecursiveGaussianImageFilter(const vtkvmtkRecursiveGaussianImageFilter&);  // Not implemented.
  void operator=(const vtkvmtkRecursiveGaussianImageFilter&);  // Not implemented.

  double Sigma;
  int NormalizeAcrossScale;
};

#endif


