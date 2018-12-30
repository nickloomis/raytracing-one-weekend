BINARYPATH="bazel-bin/ray_tracer/"
IMAGE_FILENAME="traced_image.ppm"
echo "Removing test.ppm file..."
rm ${IMAGE_FILENAME}
echo "Running ray tracer..."
${BINARYPATH}/trace
echo "Displaying result (test.ppm)..."
display -sample 400% ${IMAGE_FILENAME}
