SET(SRC_CPP_FILES
  
)

SET(INTERNAL_CPP_FILES
  QmitkBasicImageProcessingView.cpp

)

SET(UI_FILES
  src/internal/QmitkBasicImageProcessingViewControls.ui
)

SET(MOC_H_FILES
  src/internal/QmitkBasicImageProcessingView.h
)

SET(RESOURCE_FILES
  resources/lena.xpm
)

SET(RES_FILES
# uncomment the following line if you want to use Qt resources
  resources/QmitkBasicImageProcessingView.qrc
)

SET(CPP_FILES manifest.cpp)

foreach(file ${SRC_CPP_FILES})
  SET(CPP_FILES ${CPP_FILES} src/${file})
endforeach(file ${SRC_CPP_FILES})

foreach(file ${INTERNAL_CPP_FILES})
  SET(CPP_FILES ${CPP_FILES} src/internal/${file})
endforeach(file ${INTERNAL_CPP_FILES})

