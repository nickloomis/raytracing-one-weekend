BINARYPATH="bazel-bin/ray_tracer/"
echo "Removing test.ppm file..."
rm ${BINARYPATH}test.ppm
echo "Running ray tracer..."
${BINARYPATH}/trace >> ${BINARYPATH}test.ppm
echo "Displaying result (test.ppm)..."
display -sample 400% ${BINARYPATH}test.ppm
