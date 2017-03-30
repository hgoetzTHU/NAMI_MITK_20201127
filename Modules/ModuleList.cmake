# The entries in the mitk_modules list must be
# ordered according to their dependencies.

set(mitk_modules
  Core
  CommandLine
  AppUtil
  DCMTesting
  RDF
  LegacyIO
  DataTypesExt
  Overlays
  LegacyGL
  AlgorithmsExt
  MapperExt
  DICOMReader
  DICOMReaderServices
  DICOMTesting
  SceneSerializationBase
  PlanarFigure
  ImageDenoising
  ImageExtraction
  LegacyAdaptors
  SceneSerialization
  Gizmo
  GraphAlgorithms
  Multilabel
  ImageStatistics
  ContourModel
  SurfaceInterpolation
  Segmentation
  PlanarFigureSegmentation
  OpenViewCore
  QtWidgets
  QtWidgetsExt
  C3js
  QmlItems
  SegmentationUI
  DiffusionImaging
  GPGPU
  OpenIGTLink
  IGTBase
  IGT
  CameraCalibration
  RigidRegistration
  RigidRegistrationUI
  DeformableRegistration
  DeformableRegistrationUI
  OpenCL
  OpenCVVideoSupport
  QtOverlays
  ToFHardware
  ToFProcessing
  ToFUI
  US
  USUI
  DicomUI
  Simulation
  Remeshing
  Python
  QtPython
  Persistence
  OpenIGTLinkUI
  IGTUI
  VtkShaders
  DicomRT
  RTUI
  IOExt
  XNAT
  TubeGraph
  BiophotonicsHardware
  Classification
  TumorInvasionAnalysis
  MatchPointRegistration
  MatchPointRegistrationUI
  BoundingShape
  CEST
)

if(MITK_ENABLE_PIC_READER)
  list(APPEND mitk_modules IpPicSupportIO)
endif()
