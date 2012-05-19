/*=========================================================================

Program:   VMTK
Module:    $RCSfile: vtkbvsVesselEnhancingDiffusion3DImageFilter.cxx,v $
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

#include "vtkvmtkVesselEnhancingDiffusion3DImageFilter.h"
#include "vtkImageData.h"
#include "vtkObjectFactory.h"

#include "vtkvmtkITKFilterUtilities.h"

#include "itkVesselEnhancingDiffusion3DImageFilter.h"

vtkCxxRevisionMacro(vtkvmtkVesselEnhancingDiffusion3DImageFilter, "$Revision: 1.2 $");
vtkStandardNewMacro(vtkvmtkVesselEnhancingDiffusion3DImageFilter);

vtkvmtkVesselEnhancingDiffusion3DImageFilter::vtkvmtkVesselEnhancingDiffusion3DImageFilter()
{
  this->SigmaMin = 0.0;
  this->SigmaMax = 0.0;
  this->NumberOfSigmaSteps = 0;
  this->SigmaStepMethod = EQUISPACED;
  this->TimeStep = 0.001;
  this->Epsilon = 0.01;
  this->Omega = 25.0;
  this->Sensitivity = 5.0;
  this->NumberOfIterations = 30;
  this->Alpha = 0.5;
  this->Beta = 0.5;
  this->Gamma = 5.0;
  this->RecalculateVesselness = 100;
}

vtkvmtkVesselEnhancingDiffusion3DImageFilter::~vtkvmtkVesselEnhancingDiffusion3DImageFilter()
{
}

double vtkvmtkVesselEnhancingDiffusion3DImageFilter::ComputeSigmaValue(int scaleLevel)
{
  double sigmaValue;

  if (this->NumberOfSigmaSteps < 2)
  {
    return this->SigmaMin;
  }

  switch (this->SigmaStepMethod)
    {
    case EQUISPACED:
      {
      double stepSize = ( SigmaMax - SigmaMin ) / (NumberOfSigmaSteps-1);
      if (stepSize < 1e-10)
        {
        stepSize = 1e-10;
        }
      sigmaValue = SigmaMin + stepSize * scaleLevel;
      break;
      }
    case LOGARITHMIC:
      {
      double stepSize = ( vcl_log(SigmaMax) - vcl_log(SigmaMin) ) / (NumberOfSigmaSteps-1);
      if (stepSize < 1e-10)
        {
        stepSize = 1e-10;
        }
      sigmaValue = vcl_exp( vcl_log (SigmaMin) + stepSize * scaleLevel);
      break;
      }
    default:
      vtkErrorMacro("Error: undefined sigma step method.");
      sigmaValue = 0.0;
      break;
    }

  return sigmaValue;
}

void vtkvmtkVesselEnhancingDiffusion3DImageFilter::SimpleExecute(vtkImageData *input, vtkImageData *output)
{
  std::vector<float> scales;
  for (int i=0; i<this->NumberOfSigmaSteps; i++)
    {
    scales.push_back(this->ComputeSigmaValue(i));
    }

  typedef itk::Image<float,3> ImageType;

  ImageType::Pointer inImage = ImageType::New();

  vtkvmtkITKFilterUtilities::VTKToITKImage<ImageType>(input,inImage);

  typedef itk::VesselEnhancingDiffusion3DImageFilter<float,3> ImageFilterType;

  ImageFilterType::Pointer imageFilter = ImageFilterType::New();
  imageFilter->SetInput(inImage);
  imageFilter->SetScales(scales);
  imageFilter->SetTimeStep(this->TimeStep);
  imageFilter->SetEpsilon(this->Epsilon);
  imageFilter->SetOmega(this->Omega);
  imageFilter->SetSensitivity(this->Sensitivity);
  imageFilter->SetIterations(this->NumberOfIterations);
  imageFilter->SetAlpha(this->Alpha);
  imageFilter->SetBeta(this->Beta);
  imageFilter->SetGamma(this->Gamma);
  imageFilter->SetRecalculateVesselness(this->RecalculateVesselness);
  imageFilter->Update();

  vtkvmtkITKFilterUtilities::ITKToVTKImage<ImageType>(imageFilter->GetOutput(),output);
}

