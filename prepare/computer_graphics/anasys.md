# ANSYS 有限元分析

## 使用 STL obj 等网格模型进行有限元分析

STL 文件是三角形网格文件，是由三角形面片的法向量和顶点组成，首先要将其转化为实体，才能进行有限元分析。

主要操作：

1. 新建 static structural 工程；
2. 导入网格模型到 Geometry;
3. 进入 SpaceClaim中，在 Facets 菜单检查网格模型的质量，并使用 Auto Fix 修补；
4. 右键 Structure 中模型的层级，选择把网格模型转换成实体模型，方便后一步划分网格；
5. 在 Model 中对几何模型进行四面体化或者六面体化；
6. 施加力，进行有限元分析；

## Reference

1. [STL格式的文件导入ANSYS，Abaqus，HyperMesh](http://www.1cae.com/a/ansys/45/stl-ansys-abaqus-hypermesh-workbench-3430.htm)
2. [从STL文件生成有限元FEA网格](https://zhuanlan.zhihu.com/p/198751589)
3. [solidworks能不能对stl模型做有限元分析？](https://www.zhihu.com/question/370527244)
4. [有限元网格划分和网格细化](https://cn.comsol.com/multiphysics/mesh-refinement)
