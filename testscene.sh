BINARYPATH="bazel-bin/ray_tracer/"
IMAGE_FILENAME="traced_image.ppm"
echo "Removing test.ppm file..."
rm ${IMAGE_FILENAME}
echo "Running ray tracer..."
${BINARYPATH}/trace --aperture_diameter=0.05
echo "Displaying result (test.ppm)..."
display -sample 400% ${IMAGE_FILENAME}
