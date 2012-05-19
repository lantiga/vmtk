/*=========================================================================

Program:   VMTK
Module:    $RCSfile: vtkvmtkThresholdSegmentationLevelSetImageFilter.cxx,v $
Language:  C++
Date:      $Date: 2006/04/06 16:48:25 $
Version:   $Revision: 1.1 $

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

#include "vtkvmtkThresholdSegmentationLevelSetImageFilter.h"
#include "vtkImageData.h"
#include "vtkObjectFactory.h"

#include "vtkvmtkITKFilterUtilities.h"

#include "itkThresholdSegmentationLevelSetImageFilter.h"

vtkCxxRevisionMacro(vtkvmtkThresholdSegmentationLevelSetImageFilter, "$Revision: 1.4 $");
vtkStandardNewMacro(vtkvmtkThresholdSegmentationLevelSetImageFilter);

vtkvmtkThresholdSegmentationLevelSetImageFilter::vtkvmtkThresholdSegmentationLevelSetImageFilter()
{
  this->UpperThreshold = 0.0;
  this->LowerThreshold = 0.0;
  this->EdgeWeight = 1.0;
  this->SmoothingIterations = 0;
  this->SmoothingTimeStep = 0.01;
  this->SmoothingConductance = 1.0;

  this->IsoSurfaceValue = 0.0;
  this->NumberOfIterations = 0;
  this->PropagationScaling = 1.0;
  this->CurvatureScaling = 0.0;
  this->AdvectionScaling = 0.0;
  this->MaximumRMSError = 0.0;
  this->UseNegativeFeatures = 0;
  this->UseImageSpacing = 1;
  this->AutoGenerateSpeedAdvection = 1;
  this->InterpolateSurfaceLocation = 1;
  this->FeatureImage = NULL;
  this->SpeedImage = NULL;
  this->FeatureScaling = 1.0;
  this->RMSChange = 0.0;
  this->ElapsedIterations = 0;
}

vtkvmtkThresholdSegmentationLevelSetImageFilter::~vtkvmtkThresholdSegmentationLevelSetImageFilter()
{
  if (this->FeatureImage)
    {
    this->FeatureImage->Delete();
    this->FeatureImage = NULL;
    }
  if (this->SpeedImage)
    {
    this->SpeedImage->Delete();
    this->SpeedImage = NULL;
    }
}

void vtkvmtkThresholdSegmentationLevelSetImageFilter::SimpleExecute(vtkImageData *input, vtkImageData *output)
{
  typedef itk::Image<float,3> ImageType;

  ImageType::Pointer inImage = ImageType::New();
  ImageType::Pointer featureImage = ImageType::New();
  ImageType::Pointer speedImage = ImageType::New();

  vtkvmtkITKFilterUtilities::VTKToITKImage<ImageType>(input,inImage);
  vtkvmtkITKFilterUtilities::VTKToITKImage<ImageType>(this->FeatureImage,featureImage);
  vtkvmtkITKFilterUtilities::VTKToITKImage<ImageType>(this->SpeedImage,speedImage);

  typedef itk::ThresholdSegmentationLevelSetImageFilter<ImageType,ImageType> ImageFilterType;

  ImageFilterType::Pointer imageFilter = ImageFilterType::New();
  imageFilter->SetInput(inImage);
  imageFilter->SetUpperThreshold(this->UpperThreshold);
  imageFilter->SetLowerThreshold(this->LowerThreshold);
  imageFilter->SetEdgeWeight(this->EdgeWeight);
  imageFilter->SetSmoothingIterations(this->SmoothingIterations);
  imageFilter->SetSmoothingTimeStep(this->SmoothingTimeStep);
  imageFilter->SetSmoothingConductance(this->SmoothingConductance);
  imageFilter->SetIsoSurfaceValue(this->IsoSurfaceValue);
  imageFilter->SetNumberOfIterations(this->NumberOfIterations);
  imageFilter->SetPropagationScaling(this->PropagationScaling);
  imageFilter->SetCurvatureScaling(this->CurvatureScaling);
  imageFilter->SetAdvectionScaling(this->AdvectionScaling);
  imageFilter->SetMaximumRMSError(this->MaximumRMSError);
  imageFilter->SetUseNegativeFeatures(this->UseNegativeFeatures);
  imageFilter->SetUseImageSpacing(this->UseImageSpacing);
  imageFilter->SetAutoGenerateSpeedAdvection(this->AutoGenerateSpeedAdvection);
  imageFilter->SetInterpolateSurfaceLocation(this->InterpolateSurfaceLocation);
  imageFilter->SetFeatureImage(featureImage);
  imageFilter->SetSpeedImage(speedImage);
  imageFilter->SetFeatureScaling(this->FeatureScaling);
  imageFilter->Update();

  this->RMSChange = imageFilter->GetRMSChange();
  this->ElapsedIterations = imageFilter->GetElapsedIterations();

  vtkvmtkITKFilterUtilities::ITKToVTKImage<ImageType>(imageFilter->GetOutput(),output);
}


