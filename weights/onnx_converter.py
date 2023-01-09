import argparse

import onnx
import onnxsim
import torch

parser = argparse.ArgumentParser()
parser.add_argument(
    "--output-filename",
    default="test.onnx",
    help="give the path to save the converted model (.onnx)"
)
parser.add_argument(
    "--model-path",
    help="give the path to save the converted model (.onnx)"
)
parser.add_argument(
    "--input-shape",
    nargs='+',
    type=int,
    default=[1, 3, 640, 640],
    help="give the input shape as e.g. --input-shape 1 3 640 640"
)
parser.add_argument(
    "--yolo-path",
    default=None,
    help="if using custom yolov5 model, give the path to yolov5 cloned folder"
)
args = parser.parse_args()

# For custom yolov5 model pass
# model = torch.hub.load("/path/to/yolov5/folder", "custom", path="path/to/model.pt", source="local")
if not isinstance(args.yolo_path, str):
    model = torch.load(args.model_path)
else:
    model = torch.hub.load(args.yolo_path, "custom", path=args.model_path, source="local")

# Base input shape for conversion
base_input = torch.zeros(*args.input_shape)

torch.onnx.export(
    model,
    base_input,
    args.output_filename,
    verbose=False,
    opset_version=12,
    do_constant_folding=True,
    input_names=['images'],
    output_names=['output'],
    dynamic_axes=None
)

model_onnx = onnx.load(args.output_filename)
onnx.checker.check_model(model_onnx)

# d = {'stride': int(max(model.stride)), 'names': model.names}
d = {'stride': int(model.stride), 'names': model.names}

for k, v in d.items():
    meta = model_onnx.metadata_props.add()
    meta.key, meta.value = k, str(v)
onnx.save(model_onnx, args.output_filename)

model_onnx, check = onnxsim.simplify(model_onnx)
onnx.save(model_onnx, args.output_filename)
