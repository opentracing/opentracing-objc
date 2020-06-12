// swift-tools-version:4.0
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "Opentracing",
    products: [
        .library( name: "Opentracing", type: .dynamic, targets: ["Opentracing"]),
        .library( name: "libOpentracing", type: .static, targets: ["Opentracing"]),
    ],
    dependencies: [
    ],
    targets: [
        .target(  name: "Opentracing",
                  dependencies: [],
                  path: "Pod",
                  sources:["Classes"],
                  publicHeadersPath: "SPMHeaders")
    ]
)

