CFLAGS=`pkg-config --cflags glib-2.0` -g -I${INCLUDEDIR}/
LDFLAGS=`pkg-config --libs glib-2.0`
CC=gcc
BIN=simulator
BINDIR=bin
INCLUDEDIR=include

all: ${BIN}

${BIN}: main.c ${BINDIR}/Simulator.o ${BINDIR}/Universe.o ${BINDIR}/Orbitals.o
	$(CC) $(LDFLAGS) $^ -o ${BIN}

${BINDIR}/Simulator.o: OrbitalSimulator/Simulator.c ${INCLUDEDIR}/Universe.h
	$(CC) ${CFLAGS} -c $< -o $@

${BINDIR}/Universe.o: OrbitalSimulator/Universe.c ${INCLUDEDIR}/Universe.h ${BINDIR}/Orbitals.o ${BINDIR}/OrbitalCollection.o ${BINDIR}/Vector3D.o ${BINDIR}/Forces.o
	$(CC) ${CFLAGS} -c $< -o $@

${BINDIR}/Orbitals.o:
	$(CC) ${CFLAGS} -c $< -o $@

${BINDIR}/OrbitalCollection.o:
	$(CC) ${CFLAGS} -c $< -o $@

${BINDIR}/Forces.o:
	$(CC) ${CFLAGS} -c $< -o $@
	
${BINDIR}/Orbits.o:
	$(CC) ${CFLAGS} -c $< -o $@

${BINDIR}/Vector3D.o:
	$(CC) ${CFLAGS} -c $< -o $@

${BINDIR}/Point3D.o:
	$(CC) ${CFLAGS} -c $< -o $@
	
${INCLUDEDIR}/Universe.h: OrbitalSimulator/Universe.h
	cp $< $@
 	
${INCLUDEDIR}/Simulator.h: OrbitalSimulator/Simulator.h
	cp $< $@

${INCLUDEDIR}/Orbital.h: OrbitalSimulator/Orbital.h
	cp $< $@
 	
${INCLUDEDIR}/Orbits.h: Mechanics/Orbits.h
	cp $< $@
 	
${INCLUDEDIR}/Forces.h: Mechanics/Forces.h
	cp $< $@
 	
${INCLUDEDIR}/Angle3D.h: Geometry/Angle3D.h
	cp $< $@
 	
${INCLUDEDIR}/Point3D.h: Geometry/Point3D.h
	cp $< $@
 	
${INCLUDEDIR}/Vector3D.h: Geometry/Vector3D.h
	cp $< $@
 	
clean:
	rm -rf ${BINDIR}/* ${INCLUDEDIR}/*