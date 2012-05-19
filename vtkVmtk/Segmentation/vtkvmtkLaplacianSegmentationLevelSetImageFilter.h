/*=========================================================================

Program:   VMTK
Module:    $RCSfile: vtkvmtkLaplacianSegmentationLevelSetImageFilter.h,v $
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

// .NAME vtkvmtkLaplacianSegmentationLevelSetImageFilter - Wrapper class around itk::LaplacianSegmentationLevelSetImageFilter
// .SECTION Description
// vtkvmtkLaplacianSegmentationLevelSetImageFilter


#ifndef __vtkvmtkLaplacianSegmentationLevelSetImageFilter_h
#define __vtkvmtkLaplacianSegmentationLevelSetImageFilter_h


#include "vtkSimpleImageToImageFilter.h"
#include "vtkImageData.h"
#include "vtkvmtkWin32Header.h"

class VTK_VMTK_SEGMENTATION_EXPORT vtkvmtkLaplacianSegmentationLevelSetImageFilter : public vtkSimpleImageToImageFilter
{
 public:
  static vtkvmtkLaplacianSegmentationLevelSetImageFilter *New();
  vtkTypeRevisionMacro(vtkvmtkLaplacianSegmentationLevelSetImageFilter, vtkSimpleImageToImageFilter);

  vtkSetMacro(IsoSurfaceValue,double);
  vtkGetMacro(IsoSurfaceValue,double);
 
  vtkSetMacro(NumberOfIterations,int);
  vtkGetMacro(NumberOfIterations,int);
  
  vtkSetMacro(PropagationScaling,double);
  vtkGetMacro(PropagationScaling,double);

  vtkSetMacro(CurvatureScaling,double);
  vtkGetMacro(CurvatureScaling,double);

  vtkSetMacro(MaximumRMSError,double);
  vtkGetMacro(MaximumRMSError,double);
 
  vtkSetMacro(UseNegativeFeatures,int);
  vtkGetMacro(UseNegativeFeatures,int);
  vtkBooleanMacro(UseNegativeFeatures,int);
 
  vtkSetMacro(UseImageSpacing,int);
  vtkGetMacro(UseImageSpacing,int);
  vtkBooleanMacro(UseImageSpacing,int);

  vtkSetMacro(InterpolateSurfaceLocation,int);
  vtkGetMacro(InterpolateSurfaceLocation,int);
  vtkBooleanMacro(InterpolateSurfaceLocation,int);

  vtkSetObjectMacro(FeatureImage,vtkImageData);
  vtkGetObjectMacro(FeatureImage,vtkImageData);
 
  vtkSetObjectMacro(SpeedImage,vtkImageData);
  vtkGetObjectMacro(SpeedImage,vtkImageData);
 
  vtkSetMacro(FeatureScaling,double);
  vtkGetMacro(FeatureScaling,double);
 
  vtkGetMacro(RMSChange,double);
 
  vtkGetMacro(ElapsedIterations,int);
  
protected:

  vtkvmtkLaplacianSegmentationLevelSetImageFilter();
  ~vtkvmtkLaplacianSegmentationLevelSetImageFilter();

  void SimpleExecute(vtkImageData *input, vtkImageData *output);

  double IsoSurfaceValue;
  int NumberOfIterations;
  double PropagationScaling;
  double CurvatureScaling;
  double MaximumRMSError;
  int UseNegativeFeatures;
  int UseImageSpacing;
  int InterpolateSurfaceLocation;
  vtkImageData* FeatureImage;
  vtkImageData* SpeedImage;
  double FeatureScaling;
  double RMSChange;
  int ElapsedIterations;

private:
  vtkvmtkLaplacianSegmentationLevelSetImageFilter(const vtkvmtkLaplacianSegmentationLevelSetImageFilter&);  // Not implemented.
  void operator=(const vtkvmtkLaplacianSegmentationLevelSetImageFilter&);  //
                                                                          // Not implemented
};

#endif


