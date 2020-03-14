JFLAGS = -g
JC = javac
.SUFFIXES: .java .class
.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = \
	DemoMain.java \
	cse241_hw7/AbstractBoard.java \
	cse241_hw7/BoardArray1D.java \
	cse241_hw7/BoardArray2D.java \
	cse241_hw7/GlobalFunction.java

default: classes

classes: $(CLASSES:.java=.class)

clean:
	$(RM) *.class
