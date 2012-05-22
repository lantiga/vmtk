/*=========================================================================

Program:   VMTK
Module:    $RCSfile: vtkvmtkFWHMFeatureImageFilter.h,v $
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

// .NAME vtkvmtkCollidingFrontsImageFilter - Wrapper class around itk::CollidingFrontsImageFilter
// .SECTION Description
// vtkvmtkCollidingFrontsImageFilter


#ifndef __vtkvmtkFWHMFeatureImageFilter_h
#define __vtkvmtkFWHMFeatureImageFilter_h

#include "vtkSimpleImageToImageFilter.h"
#include "vtkvmtkWin32Header.h"

class VTK_VMTK_SEGMENTATION_EXPORT vtkvmtkFWHMFeatureImageFilter : public vtkSimpleImageToImageFilter
{
 public:
  static vtkvmtkFWHMFeatureImageFilter *New();
  vtkTypeRevisionMacro(vtkvmtkFWHMFeatureImageFilter, vtkSimpleImageToImageFilter);

  vtkSetMacro(UseImageSpacing,int);
  vtkGetMacro(UseImageSpacing,int);
  vtkBooleanMacro(UseImageSpacing,int);

  vtkSetVectorMacro(Radius,int,3);
  vtkGetVectorMacro(Radius,int,3);

  vtkSetMacro(BackgroundValue,float);
  vtkGetMacro(BackgroundValue,float);
 
protected:
  vtkvmtkFWHMFeatureImageFilter();
  ~vtkvmtkFWHMFeatureImageFilter();

  void SimpleExecute(vtkImageData *input, vtkImageData *output);

  int UseImageSpacing;
  int Radius[3];
  float BackgroundValue;

private:
  vtkvmtkFWHMFeatureImageFilter(const vtkvmtkFWHMFeatureImageFilter&);  // Not implemented.
  void operator=(const vtkvmtkFWHMFeatureImageFilter&);  // Not implemented.
};

#endif
