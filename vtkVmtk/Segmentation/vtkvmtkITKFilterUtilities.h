/*=========================================================================

Program:   VMTK
Module:    vtkvmtkITKFilterUtilities.h
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

// .NAME vtkvmtkITKFilterUtilities - Abstract class for wrapping ITK filters
// .SECTION Description
// vtkvmtkSimpleImageToImageITKFilter


#ifndef __vtkvmtkITKFilterUtilities_h
#define __vtkvmtkITKFilterUtilities_h

#include "vtkvmtkITKFilterUtilities.h"
#include "vtkvmtkWin32Header.h"

#include "vtkImageData.h"
#include "itkImage.h"
#include "itkImportImageContainer.h"

class VTK_VMTK_SEGMENTATION_EXPORT vtkvmtkITKFilterUtilities
{
public:

  template<typename TImage>
  static void
  VTKToITKImage(vtkImageData* input, typename TImage::Pointer output) {

    typedef TImage ImageType;
    typedef typename ImageType::Pointer ImagePointer;
    typedef typename ImageType::PixelType PixelType;

    int dims[3];
    input->GetDimensions(dims);
    double spacing[3];
    input->GetSpacing(spacing);
    double origin[3];
    input->GetOrigin(origin);

//    output->GetPixelContainer()->SetImportPointer(static_cast<PixelType*>(input->GetScalarPointer()),dims[0]*dims[1]*dims[2],false);

    typename ImageType::PointType point;
    point[0] = origin[0];
    point[1] = origin[1];
    point[2] = origin[2];
    typename ImageType::RegionType region;
    typename ImageType::IndexType index;
    typename ImageType::SizeType size;
    index[0] = index[1] = index[2] = 0;
    size[0] = dims[0];
    size[1] = dims[1];
    size[2] = dims[2];
    region.SetIndex(index);
    region.SetSize(size);
    output->SetLargestPossibleRegion(region);
    output->SetBufferedRegion(region);
    output->SetSpacing(spacing);
    output->SetOrigin(origin);

    output->Allocate();
    int i = 0;
    vtkIdType numberOfPoints = input->GetNumberOfPoints();
    typename ImageType::PixelContainerPointer pixelContainer = output->GetPixelContainer();
    void* scalarPointer = input->GetScalarPointer();
    for (i=0; i<numberOfPoints; i++)
      {
      (*pixelContainer)[i] = *(static_cast<PixelType*>(scalarPointer)+i);
      }
  }

  template<typename TImage>
  static void
  VTKToITKImage2D(vtkImageData* input, typename TImage::Pointer output) {

    typedef TImage ImageType;
    typedef typename ImageType::Pointer ImagePointer;
    typedef typename ImageType::PixelType PixelType;

    int dims[3];
    input->GetDimensions(dims);
    double spacing[3];
    input->GetSpacing(spacing);
    double origin[3];
    input->GetOrigin(origin);

    double outputSpacing[2];
    outputSpacing[0] = spacing[0];
    outputSpacing[1] = spacing[1];

    typename ImageType::PointType point;
    point[0] = origin[0];
    point[1] = origin[1];

    //output->GetPixelContainer()->SetImportPointer(static_cast<PixelType*>(input->GetScalarPointer()),dims[0]*dims[1],false);
    typename ImageType::RegionType region;
    typename ImageType::IndexType index;
    typename ImageType::SizeType size;
    index[0] = index[1] = 0;
    size[0] = dims[0];
    size[1] = dims[1];
    region.SetIndex(index);
    region.SetSize(size);
    output->SetLargestPossibleRegion(region);
    output->SetBufferedRegion(region);
    output->SetSpacing(outputSpacing);

    output->Allocate();
    int i = 0;
    vtkIdType numberOfPoints = input->GetNumberOfPoints();
    typename ImageType::PixelContainerPointer pixelContainer = output->GetPixelContainer();
    void* scalarPointer = input->GetScalarPointer();
    for (i=0; i<numberOfPoints; i++)
      {
      (*pixelContainer)[i] = *(static_cast<PixelType*>(scalarPointer)+i);
      }
  }

  template<typename TImage>
  static void
  ITKToVTKImage(const TImage* input, vtkImageData* output, int scalarType = VTK_FLOAT) {

    typedef TImage ImageType;
    typedef typename ImageType::PixelType PixelType;
    typedef typename ImageType::SpacingType SpacingType;
    typedef typename ImageType::PointType PointType;
    typedef typename ImageType::RegionType RegionType;

    typename ImageType::RegionType region;

    unsigned int dim = input->GetImageDimension();

    int dims[3];
    double spacing[3];
    double origin[3];
 
    const RegionType& inputRegion = input->GetBufferedRegion();
    dims[0] = inputRegion.GetSize()[0];
    dims[1] = inputRegion.GetSize()[1];

    const PointType& inputOrigin = input->GetOrigin();
    origin[0] = inputOrigin[0];
    origin[1] = inputOrigin[1];

    const SpacingType& inputSpacing = input->GetSpacing();
    spacing[0] = inputSpacing[0];
    spacing[1] = inputSpacing[1];

    if (dim == 3)
      {
      spacing[2] = inputSpacing[2];
      origin[2] = inputOrigin[2];
      dims[2] = inputRegion.GetSize()[2];
      }

    output->SetOrigin(origin);
    output->SetSpacing(spacing);
    output->SetExtent(0,dims[0]-1,0,dims[1]-1,0,dims[2]-1);
    output->SetScalarType(scalarType);
    output->AllocateScalars();

    memcpy(static_cast<PixelType*>(output->GetScalarPointer()),input->GetBufferPointer(),input->GetBufferedRegion().GetNumberOfPixels()*sizeof(PixelType));
  }
/*
  template<typename TImage>
  static void
  ITKToVTKImage(const typename TImage::Pointer input, vtkImageData* output) {

    typedef TImage ImageType;
    typedef typename ImageType::Pointer ImagePointer;
    typedef typename ImageType::PixelType PixelType;

    //TODO: make sure output has the right number of pixels

    memcpy(static_cast<PixelType*>(output->GetScalarPointer()),input->GetBufferPointer(),input->GetBufferedRegion().GetNumberOfPixels()*sizeof(PixelType));
  }
*/
protected:
  vtkvmtkITKFilterUtilities() {};
  ~vtkvmtkITKFilterUtilities() {};

private:
  vtkvmtkITKFilterUtilities(const vtkvmtkITKFilterUtilities&);  // Not implemented.
  void operator=(const vtkvmtkITKFilterUtilities&);  // Not implemented.
};

#if 0
template< class TInputPixel, class TOutputPixel>
void
vtkvmtkSimpleImageToImageITKFilter<TInputPixel,TOutputPixel>::
SimpleExecute(vtkImageData *input, vtkImageData *output)
{
  int inputDims[3];
  input->GetDimensions(inputDims);
  double inputSpacing[3];
  input->GetSpacing(inputSpacing);

  InputImagePointer inImage = InputImageType::New();
  inImage->GetPixelContainer()->SetImportPointer(static_cast<InputPixelType*>(input->GetScalarPointer()),inputDims[0]*inputDims[1]*inputDims[2],false);
  typename InputImageType::RegionType inputRegion;
  typename InputImageType::IndexType inputIndex;
  typename InputImageType::SizeType inputSize;
  inputIndex[0] = inputIndex[1] = inputIndex[2] = 0;
  inputSize[0] = inputDims[0];
  inputSize[1] = inputDims[1];
  inputSize[2] = inputDims[2];
  inputRegion.SetIndex(inputIndex);
  inputRegion.SetSize(inputSize);
  inImage->SetLargestPossibleRegion(inputRegion);
  inImage->SetBufferedRegion(inputRegion);
  inImage->SetSpacing(inputSpacing);

  int outputDims[3];
  output->GetDimensions(outputDims);
  double outputSpacing[3];
  output->GetSpacing(outputSpacing);

  OutputImagePointer outImage = OutputImageType::New();
  outImage->GetPixelContainer()->SetImportPointer(static_cast<OutputPixelType*>(output->GetScalarPointer()),outputDims[0]*outputDims[1]*outputDims[2],false);
  typename OutputImageType::RegionType outputRegion;
  typename OutputImageType::IndexType outputIndex;
  typename OutputImageType::SizeType outputSize;
  outputIndex[0] = outputIndex[1] = outputIndex[2] = 0;
  outputSize[0] = outputDims[0];
  outputSize[1] = outputDims[1];
  outputSize[2] = outputDims[2];
  outputRegion.SetIndex(outputIndex);
  outputRegion.SetSize(outputSize);
  outImage->SetLargestPossibleRegion(outputRegion);
  outImage->SetBufferedRegion(outputRegion);
  outImage->SetSpacing(outputSpacing);

  this->SimpleExecuteITK(inImage,outImage);

  memcpy(static_cast<OutputPixelType*>(output->GetScalarPointer()),outImage->GetBufferPointer(),outImage->GetBufferedRegion().GetNumberOfPixels()*sizeof(OutputPixelType));
}

typedef vtkvmtkSimpleImageToImageITKFilter<float,float> vtkvmtkSimpleImageToImageITKFilterFF;
#endif

#endif

