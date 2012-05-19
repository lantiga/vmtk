/*=========================================================================

Program:   VMTK
Module:    $RCSfile: vtkvmtkGradientMagnitudeRecursiveGaussian2DImageFilter.h,v $
Language:  C++
Date:      $Date: 2006/04/06 16:48:25 $
Version:   $Revision: 1.3 $

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

// .NAME vtkvmtkGradientMagnitudeRecursiveGaussian2DImageFilter - Wrapper class around itk::GradientMagnitudeRecursiveGaussianImageFilter
// .SECTION Description
// vtkvmtkGradientMagnitude2DImageFilter


#ifndef __vtkvmtkGradientMagnitudeRecursiveGaussian2DImageFilter_h
#define __vtkvmtkGradientMagnitudeRecursiveGaussian2DImageFilter_h


#include "vtkSimpleImageToImageFilter.h"
#include "vtkvmtkWin32Header.h"

class VTK_VMTK_SEGMENTATION_EXPORT vtkvmtkGradientMagnitudeRecursiveGaussian2DImageFilter : public vtkSimpleImageToImageFilter
{
 public:
  static vtkvmtkGradientMagnitudeRecursiveGaussian2DImageFilter *New();
  vtkTypeRevisionMacro(vtkvmtkGradientMagnitudeRecursiveGaussian2DImageFilter,vtkSimpleImageToImageFilter);

  vtkSetMacro(Sigma,double);
  vtkGetMacro(Sigma,double);

  vtkSetMacro(NormalizeAcrossScale,int);
  vtkGetMacro(NormalizeAcrossScale,int);
  vtkBooleanMacro(NormalizeAcrossScale,int);

protected:
  vtkvmtkGradientMagnitudeRecursiveGaussian2DImageFilter();
  ~vtkvmtkGradientMagnitudeRecursiveGaussian2DImageFilter() {};
  
  void SimpleExecute(vtkImageData *input, vtkImageData *output);

private:
  vtkvmtkGradientMagnitudeRecursiveGaussian2DImageFilter(const vtkvmtkGradientMagnitudeRecursiveGaussian2DImageFilter&);  // Not implemented.
  void operator=(const vtkvmtkGradientMagnitudeRecursiveGaussian2DImageFilter&);  // Not implemented.

  double Sigma;
  int NormalizeAcrossScale;
};

#endif

