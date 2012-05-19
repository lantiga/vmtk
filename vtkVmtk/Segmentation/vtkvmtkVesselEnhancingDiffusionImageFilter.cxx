/*=========================================================================

Program:   VMTK
Module:    $RCSfile: vtkbvsVesselEnhancingDiffusionImageFilter.cxx,v $
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

#include "vtkvmtkVesselEnhancingDiffusionImageFilter.h"
#include "vtkImageData.h"
#include "vtkObjectFactory.h"

#include "vtkvmtkITKFilterUtilities.h"

#include "itkAnisotropicDiffusionVesselEnhancementImageFilter.h"
#include "itkMultiScaleHessianBasedMeasureImageFilter.h"
#include "itkHessianSmoothed3DToVesselnessMeasureImageFilter.h"

vtkCxxRevisionMacro(vtkvmtkVesselEnhancingDiffusionImageFilter, "$Revision: 1.2 $");
vtkStandardNewMacro(vtkvmtkVesselEnhancingDiffusionImageFilter);

vtkvmtkVesselEnhancingDiffusionImageFilter::vtkvmtkVesselEnhancingDiffusionImageFilter()
{
  this->SigmaMin = 0.0;
  this->SigmaMax = 0.0;
  this->NumberOfSigmaSteps = 0;
  this->SigmaStepMethod = EQUISPACED;
  this->TimeStep = 0.001;
  this->Epsilon = 0.01;
  this->WStrength = 25.0;
  this->Sensitivity = 5.0;
  this->NumberOfIterations = 30;
  this->Alpha = 0.5;
  this->Beta = 0.5;
  this->Gamma = 5.0;
  this->C = 1.0;
  this->NumberOfDiffusionSubIterations = 100;
}

vtkvmtkVesselEnhancingDiffusionImageFilter::~vtkvmtkVesselEnhancingDiffusionImageFilter()
{
}

void vtkvmtkVesselEnhancingDiffusionImageFilter::SimpleExecute(vtkImageData *input, vtkImageData *output)
{
  typedef itk::Image<float,3> ImageType;

  ImageType::Pointer inImage = ImageType::New();

  vtkvmtkITKFilterUtilities::VTKToITKImage<ImageType>(input,inImage);

  typedef itk::AnisotropicDiffusionVesselEnhancementImageFilter<ImageType,ImageType> ImageFilterType;
  typedef ImageFilterType::VesselnessFilterType VesselnessFilterType;

  ImageFilterType::Pointer imageFilter = ImageFilterType::New();
  imageFilter->SetInput(inImage);
  imageFilter->GetMultiScaleVesselnessFilter()->SetSigmaMinimum(this->SigmaMin);
  imageFilter->GetMultiScaleVesselnessFilter()->SetSigmaMaximum(this->SigmaMax);
  imageFilter->GetMultiScaleVesselnessFilter()->SetNumberOfSigmaSteps(this->NumberOfSigmaSteps);
  if (this->SigmaStepMethod == EQUISPACED)
    {
    imageFilter->GetMultiScaleVesselnessFilter()->SetSigmaStepMethodToEquispaced();
    }
  else if (this->SigmaStepMethod == LOGARITHMIC)
    {
    imageFilter->GetMultiScaleVesselnessFilter()->SetSigmaStepMethodToLogarithmic();
    }
  imageFilter->SetTimeStep(this->TimeStep);
  imageFilter->SetEpsilon(this->Epsilon);
  imageFilter->SetWStrength(this->WStrength);
  imageFilter->SetSensitivity(this->Sensitivity);
  imageFilter->SetNumberOfIterations(this->NumberOfIterations);
  dynamic_cast<VesselnessFilterType*>(imageFilter->GetMultiScaleVesselnessFilter())->SetAlpha(this->Alpha);
  dynamic_cast<VesselnessFilterType*>(imageFilter->GetMultiScaleVesselnessFilter())->SetBeta(this->Beta);
  dynamic_cast<VesselnessFilterType*>(imageFilter->GetMultiScaleVesselnessFilter())->SetGamma(this->Gamma);
  dynamic_cast<VesselnessFilterType*>(imageFilter->GetMultiScaleVesselnessFilter())->SetC(this->C);
  imageFilter->SetNumberOfDiffusionSubIterations(this->NumberOfDiffusionSubIterations);
  imageFilter->Update();

  vtkvmtkITKFilterUtilities::ITKToVTKImage<ImageType>(imageFilter->GetOutput(),output);
}

