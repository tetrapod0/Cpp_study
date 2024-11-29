import os
from tqdm.auto import tqdm
import shutil


def get_all_files_in_path(path, except_dirs=["Cpp_study"], target_exp_list=['cpp','h','rc']):
    if os.path.isfile(path):
        if not target_exp_list: return [path]
        if path.split('.')[-1] in target_exp_list: return [path]
        else: return []
            
    paths = []
    for name in os.listdir(path):
        if name in except_dirs: continue
        paths.append(os.path.join(path, name))

    total_paths = []
    for path in paths:
        total_paths.extend(get_all_files_in_path(path, except_dirs, target_exp_list))
    
    return total_paths


def copy_files(src_path, dst_path, except_dirs=["Cpp_study"], target_exp_list=['cpp', 'h', 'rc']):
    src_paths = get_all_files_in_path(src_path, except_dirs=except_dirs)
    func = lambda path:dst_path + path[len(src_path):]
    dst_paths = list(map(func, src_paths))
    for src, dst in tqdm(zip(src_paths, dst_paths), total=len(src_paths)):
        directory = os.path.dirname(dst)
        if not os.path.exists(directory): os.makedirs(directory)
        shutil.copy2(src, dst)



src_path = os.path.dirname(os.getcwd())
dst_path = os.getcwd()
except_dirs = [dst_path.split('\\')[-1]]
target_exp_list = ['cpp', 'h', 'rc']

copy_files(src_path, dst_path, except_dirs, target_exp_list)

