# xgb2cpp
xgb2cpp converts XGBoost raw text dump to C++ code that you can use in your C++ projects.

#### READ FIRST
This code (atm) only works on XGB models trained with 'multi:softprob' objective. If you want it to work with 'binary:logistic' or 'binary:logitraw' you'll have to tweak code-generating Python script a bit or wait for me to implement it. 

#### How to run it?
Use *generate_cpp_code.py* script to generate *xgboost_classifier.cpp*. Generated *xgboost_classifier.cpp* will contain *xgb_classify()* function that you can use to classify samples. In folder *sample* you can find *main.cpp* and *xgboost_classifier.h* files that form use case project. 

Also, there is a *pima-indian-diabetes* dataset that I used to generate dummy model. File */sample/pima-indians-diabetes/train.py* trains XGB model and creates dump.raw.txt which is raw text representation of trained model. 

Example run:
```
cd sample/pima-indians-diabetes
# Train model and generate dump.raw.txt
python train.py
cd ../../
# Generate xgboost_classifier.cpp
python python generate_cpp_code.py --num_classes=2 --xgb_dump=sample/pima-indians-diabetes/dump.raw.txt
# Copy xgboost_classifier.cpp to sample project
cp xgboost_classifier.cpp sample/codeblocks_project/xgboost_classifier.cpp
# Now build and run main.cpp, xgboost_classifier.cpp and xgboost_classifier.h in sample/codeblocks_project
```

If you have any questions or improvements just open issue and I'll be on it. Thanks
