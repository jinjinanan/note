# workspace&target

## workspace

 > A workspace is an Xcode document that **groups** projects and other documents **so** you can work on them together. A workspace can contain any number of Xcode projects, **plus** any other files you want to include. **In addition to** organizing all the files in each Xcode project, a workspace provides implicit and explicit relationships **among** the included projects and their targets.

 workspace 是 Xcode 的一个给project和其他文档分组的文件文档，所以你可以工作。 一个workspace 可以包含任意数量的 XCode projet,任何你想添加的其他文件。此外组织所有在每个 Xcode Projiect 中的的所有文件，workspace 提供 projects 和 targets 之间隐式或显式的关系

 一个 workspace 的 project 们共用一个编译路径。

 workspace 的存在是为了解决原来仅有 project 的时候不同的 project 之间的引用和调用困难的问题。

## project

 > An Xcode project is a repository for all the files, resources, and information **required to build one or more software products.** A project contains all the elements used to build your products and maintains the relationships between those elements. It contains one or more targets, which specify how to build products. A project defines default build settings for all the targets in the project (each target can also specify its own build settings, which override the project build settings)

Xcode project 是一个为所有文件，资源和信息的个库

## scheme

在 project 的最后这么写着
> You use Xcode schemes to specify which target, build configuration, and executable configuration is active at a given time.

你可以使用 Xcode scheme 去每次定制哪个 target ，build configuration 和 executable configuration 激活

定义
>An Xcode scheme defines a collection of targets to build, a configuration to use when building, and a collection of tests to execute.

Xcode scheme 定义一个 去构建的target ，当构建时候使用的 configuration 和 去执行的测试的集合 的集合

## target

> A target specifies a product to build and contains the instructions for building the product from a set of files in a project or workspace. A target defines a single product; **it organizes the inputs into the build system—the source files and instructions for processing those source files—required to build that product.** Projects can contain one or more targets, **each of which produces one product.**

target 制定 一个去构建和包含来自 project 或 workspace 的文件集 为构建产品 的指令。一个 target 定义单独的产品。project 可以包含一个或多个 target。

## 参考
[教程](https://segmentfault.com/a/1190000003101065)