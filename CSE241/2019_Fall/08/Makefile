JFLAGS = -g
JC = javac
.SUFFIXES: .java .class
.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = \
	testMain.java \
	cse241_hw8/GTUContainer.java \
	cse241_hw8/GTUContainerDerived.java \
	cse241_hw8/GTUSet.java \
	cse241_hw8/GTUVector.java \
	cse241_hw8/GTUIterator.java

default: classes

classes: $(CLASSES:.java=.class)

clean:
	$(RM) *.class
