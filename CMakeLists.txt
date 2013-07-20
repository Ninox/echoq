CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(echoq)

SET (EQ_SRC_ROOT ${})
# SET dependences

# SET base
SET (
      ${EQ_SRC_ROOT}/explain.cc
${EQ_SRC_ROOT}/io.cc
${EQ_SRC_ROOT}/log.cc
${EQ_SRC_ROOT}/stat.cc
${EQ_SRC_ROOT}/taskqueue.cc
${EQ_SRC_ROOT}/utils.cc
${EQ_SRC_ROOT}/zip.cc
    )
# SET core
SET (EQ_SRC 
      ${EQ_SRC_ROOT}/echoq.cc
      ${EQ_SRC_ROOT}/eqAcceptor.cc
      ${EQ_SRC_ROOT}/eqContext.cc
      ${EQ_SRC_ROOT}/eqProto.cc
      ${EQ_SRC_ROOT}/eqSocket.cc
      ${EQ_SRC_ROOT}/eqTimer.cc
      ${EQ_SRC_ROOT}/eqWorker.cc
    )

#------------------- project client --------------------
