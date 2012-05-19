/*=========================================================================

Program:   VMTK
Module:    $RCSfile: vtkvmtkFastMarchingDirectionalFreezeImageFilter.h,v $
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

// .NAME vtkvmtkFastMarchingDirectionalFreezeImageFilter - Wrapper class around itk::FastMarchingDirectionalFreezeImageFilter
// .SECTION Description
// vtkvmtkFastMarchingDirectionalFreezeImageFilter


#ifndef __vtkvmtkFastMarchingDirectionalFreezeImageFilter_h
#define __vtkvmtkFastMarchingDirectionalFreezeImageFilter_h

#include "vtkSimpleImageToImageFilter.h"
#include "vtkIdList.h"
#include "vtkvmtkWin32Header.h"

class VTK_VMTK_SEGMENTATION_EXPORT vtkvmtkFastMarchingDirectionalFreezeImageFilter : public vtkSimpleImageToImageFilter
{
 public:
  static vtkvmtkFastMarchingDirectionalFreezeImageFilter *New();
  vtkTypeRevisionMacro(vtkvmtkFastMarchingDirectionalFreezeImageFilter, vtkSimpleImageToImageFilter);

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
  vtkvmtkFastMarchingDirectionalFreezeImageFilter();
  ~vtkvmtkFastMarchingDirectionalFreezeImageFilter(); 
 
  void SimpleExecute(vtkImageData *input, vtkImageData *output);

  int GenerateGradientImage;
  int TargetReachedMode;
  float TargetValue;
  double TargetOffset;
 
  vtkIdList* Seeds;
  vtkIdList* Targets;
                                                                            
private:
  vtkvmtkFastMarchingDirectionalFreezeImageFilter(const vtkvmtkFastMarchingDirectionalFreezeImageFilter&);  // Not implemented.
  void operator=(const vtkvmtkFastMarchingDirectionalFreezeImageFilter&);  // Not implemented.
};

#endif
