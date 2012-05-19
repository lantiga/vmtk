/*=========================================================================

Program:   VMTK
Module:    $RCSfile: vtkvmtkVesselEnhancingDiffusion3DImageFilter.h,v $
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

// .NAME vtkvmtkVesselEnhancingDiffusion3DImageFilter - Wrapper class around itk::VesselEnhancingDiffusion3DImageFilter
// .SECTION Description
// vtkvmtkVesselEnhancingDiffusion3DImageFilter


#ifndef __vtkvmtkVesselEnhancingDiffusion3DImageFilter_h
#define __vtkvmtkVesselEnhancingDiffusion3DImageFilter_h

#include "vtkSimpleImageToImageFilter.h"
#include "vtkvmtkWin32Header.h"

class VTK_VMTK_SEGMENTATION_EXPORT vtkvmtkVesselEnhancingDiffusion3DImageFilter : public vtkSimpleImageToImageFilter
{
 public:
  static vtkvmtkVesselEnhancingDiffusion3DImageFilter *New();
  vtkTypeRevisionMacro(vtkvmtkVesselEnhancingDiffusion3DImageFilter, vtkSimpleImageToImageFilter);

  vtkSetMacro(SigmaMin,double);
  vtkGetMacro(SigmaMin,double);

  vtkSetMacro(SigmaMax,double);
  vtkGetMacro(SigmaMax,double);

  vtkSetMacro(NumberOfSigmaSteps,int);
  vtkGetMacro(NumberOfSigmaSteps,int);

  vtkGetMacro(SigmaStepMethod,int);
  vtkSetMacro(SigmaStepMethod,int);
  void SetSigmaStepMethodToEquispaced()
  {
    this->SetSigmaStepMethod(EQUISPACED);
  }
  
  void SetSigmaStepMethodToLogarithmic()
  {
    this->SetSigmaStepMethod(LOGARITHMIC);
  }

  vtkSetMacro(TimeStep,double);
  vtkGetMacro(TimeStep,double);

  vtkSetMacro(Epsilon,double);
  vtkGetMacro(Epsilon,double);

  vtkSetMacro(Omega,double);
  vtkGetMacro(Omega,double);

  vtkSetMacro(Sensitivity,double);
  vtkGetMacro(Sensitivity,double);

  vtkSetMacro(NumberOfIterations,int);
  vtkGetMacro(NumberOfIterations,int);

  vtkSetMacro(Alpha,double);
  vtkGetMacro(Alpha,double);

  vtkSetMacro(Beta,double);
  vtkGetMacro(Beta,double);

  vtkSetMacro(Gamma,double);
  vtkGetMacro(Gamma,double);

  vtkSetMacro(RecalculateVesselness,int);
  vtkGetMacro(RecalculateVesselness,int);

  double ComputeSigmaValue(int scaleLevel);

//BTX
  enum
  {
    EQUISPACED,
    LOGARITHMIC
  };
//ETX

protected:
  vtkvmtkVesselEnhancingDiffusion3DImageFilter(); 
  ~vtkvmtkVesselEnhancingDiffusion3DImageFilter(); 

  void SimpleExecute(vtkImageData *input, vtkImageData *output);

  double SigmaMin;
  double SigmaMax;
  int NumberOfSigmaSteps;
  int SigmaStepMethod;

  double TimeStep;
  double Epsilon;
  double Omega;
  double Sensitivity;
  int NumberOfIterations;
  double Alpha;
  double Beta;
  double Gamma;
  int RecalculateVesselness;

private:
  vtkvmtkVesselEnhancingDiffusion3DImageFilter(const vtkvmtkVesselEnhancingDiffusion3DImageFilter&);  // Not implemented.
  void operator=(const vtkvmtkVesselEnhancingDiffusion3DImageFilter&);  // Not implemented.
};

#endif




