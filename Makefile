.PHONY: default
default:
	@echo Please specify make target

POD_SPEC := opentracing.podspec

publish: increment_version publish_pod

publish_pod:
	@echo "Publishing as a pod..."
	@echo "You may need to first run:"
	@echo "     pod trunk register info@opentracing.io 'OpenTracing' --description='OpenTracing'"
	@echo
	@echo "...to ensure you have publish permissions."
	@echo
	@echo "Pushing pod..."
	pod trunk push --verbose opentracing.podspec

# Bumps the version number of the Pod
increment_version:
	awk 'BEGIN { FS = "." }; { printf("%d.%d.%d", $$1, $$2, $$3+1) }' VERSION > VERSION.incr
	mv VERSION.incr VERSION
	echo "// GENERATED FILE: Do not edit directly\n#define OT_TRACER_VERSION @\"$(shell cat VERSION)\"\n" > Pod/Classes/OTVersion.h
	@echo "Updating the version string in the podspec..."
	sed 's/_VERSION_STRING_/$(shell cat VERSION)/g' opentracing.podspec.src > opentracing.podspec	
	git add .
	git commit -m "Increment version to $(shell cat VERSION)"
	git tag $(shell cat VERSION)
	git push -u origin master
	git push -u origin master --tags
	@echo Incremented version to `cat VERSION`

clean:
