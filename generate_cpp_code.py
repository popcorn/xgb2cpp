import sys
import argparse
import re

def get_single_booster_cpp_code(booster_tree, branch_id, class_index, indentation_level=0):
    level = booster_tree[branch_id].split()

    booster_code = ""

    if 'leaf' in level[0]:
        booster_code += "{0}sum[{1}] += {2};\n".format("  " * indentation_level, class_index, float(level[0].split('=')[1]))
        return booster_code

    branch_ids = level[1].split(',')
    yes_branch_id = int(branch_ids[0].split("=")[1])
    no_branch_id = int(branch_ids[1].split("=")[1])
    missing_branch_id = int(branch_ids[2].split("=")[1])
    
    # Get feature index and limit value
    feature_index = re.search('[^f]', level[0]).group(0)
    comparison = re.search('[^0-9a-zA-Z:[]+[0-9]*[0-9.]*', level[0]).group(0)
    
    booster_code += "{0}if (sample[{1}] {2}) {{\n".format("  " * indentation_level, feature_index, comparison)
    booster_code += get_single_booster_cpp_code(booster_tree, yes_branch_id, class_index, indentation_level + 1)
    booster_code += "{0}}} else {{\n".format("  " * indentation_level)
    booster_code += get_single_booster_cpp_code(booster_tree, no_branch_id, class_index, indentation_level + 1)
    booster_code += "{0}}}\n".format("  " * indentation_level)

    return booster_code

def generate_single_booster_cpp_code(booster, class_index):
    booster_tree = dict()
    for line in booster:
        branch_id = int(line.split(':')[0].strip())
        booster_tree[branch_id] = line
        
    return get_single_booster_cpp_code(booster_tree, 0, class_index, 1)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--xgb_dump', type=str, default='dump.raw.txt', help='Raw boosters dump. Created without passing feature map file to XGBoost dump() function.')
    parser.add_argument('--num_classes', type=int, required=True, help='number of classes this model is classyfing')
    
    args = parser.parse_args()

    result = ""

    result += "#include \"xgboost_classifier.h\"\n"
    result += "#include <iostream>\n"
    result += "#include <fstream>\n"
    result += "#include <vector>\n"
    result += "using namespace std;\n\n"
    result += "std::vector<float> xgb_classify(std::vector<float> &sample) {\n\n"
    result += "  std::vector<float> sum ({0}, 0.0);\n\n".format(args.num_classes)

    booster_counter = 0
    boosters = []
    with open(args.xgb_dump, 'r') as f:
        for line in f:
            if 'booster' in line:
                boosters.append([])
                booster_counter += 1
            else:
                boosters[booster_counter - 1].append(line.strip())
    
    for index, booster in enumerate(boosters):
        class_index = index % args.num_classes
        result += generate_single_booster_cpp_code(booster, class_index)
        result += "\n\n"
        
    result += "  return sum;\n"
    result += "}\n\n"

    with open('xgboost_classifier.cpp', 'w') as f:
        f.write(result)
