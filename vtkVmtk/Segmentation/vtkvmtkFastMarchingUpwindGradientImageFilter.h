/*=========================================================================

Program:   VMTK
Module:    $RCSfile: vtkvmtkFastMarchingUpwindGradientImageFilter.h,v $
Language:  C++
Date:      $Date: 2006/04/06 16:48:25 $
Version:   $Revision: 1.4 $

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

// .NAME vtkvmtkFastMarchingUpwindGradientImageFilter - Wrapper class around itk::FastMarchingUpwindGradientImageFilter
// .SECTION Description
// vtkvmtkFastMarchingUpwindGradientImageFilter


#ifndef __vtkvmtkFastMarchingUpwindGradientImageFilter_h
#define __vtkvmtkFastMarchingUpwindGradientImageFilter_h

#include "vtkSimpleImageToImageFilter.h"
#include "vtkIdList.h"
#include "vtkvmtkWin32Header.h"

class VTK_VMTK_SEGMENTATION_EXPORT vtkvmtkFastMarchingUpwindGradientImageFilter : public vtkSimpleImageToImageFilter
{
 public:
  static vtkvmtkFastMarchingUpwindGradientImageFilter *New();
  vtkTypeRevisionMacro(vtkvmtkFastMarchingUpwindGradientImageFilter, vtkSimpleImageToImageFilter);

  vtkSetMacro(GenerateGradientImage,int);
  vtkGetMacro(GenerateGradientImage,int);
  vtkBooleanMacro(GenerateGradientImage,int);

  vtkSetMacro(TargetReachedMode,int);
  vtkGetMacro(TargetReachedMode,int);
  void SetTargetReachedModeToNoTargets()
  {
    this->SetTargetReachedMode(NO_TARGETS);
  }
  void SetTargetReachedModeToOneTarget()
  {
    this->SetTargetReachedMode(ONE_TARGET);
  }
  void SetTargetReachedModeToAllTargets()
  {
    this->SetTargetReachedMode(ALL_TARGETS);
  }

  enum
  {
    NO_TARGETS,
    ONE_TARGET,
    ALL_TARGETS
  };

  vtkGetMacro(TargetValue,float);

  vtkSetMacro(TargetOffset,double);
  vtkGetMacro(TargetOffset,double);
 
  vtkSetObjectMacro(Seeds,vtkIdList);
  vtkGetObjectMacro(Seeds,vtkIdList);

  vtkSetObjectMacro(Targets,vtkIdList);
  vtkGetObjectMacro(Targets,vtkIdList);

protected:
  vtkvmtkFastMarchingUpwindGradientImageFilter();
  ~vtkvmtkFastMarchingUpwindGradientImageFilter(); 
  
  void SimpleExecute(vtkImageData *input, vtkImageData *output);

  int GenerateGradientImage;
  int TargetReachedMode;
  float TargetValue;
  double TargetOffset;
 
  vtkIdList* Seeds;
  vtkIdList* Targets;
                                                                            
private:
  vtkvmtkFastMarchingUpwindGradientImageFilter(const vtkvmtkFastMarchingUpwindGradientImageFilter&);  // Not implemented.
  void operator=(const vtkvmtkFastMarchingUpwindGradientImageFilter&);  // Not implemented.
};

#endif
