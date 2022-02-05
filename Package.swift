// swift-tools-version: 5.4

import PackageDescription

 let package = Package(
     name: "opentracing",
     platforms: [
        .iOS(.v8),
        .macOS(.v10_15)
     ],
     products: [
        .library(
            name: "opentracing",
            targets: ["opentracing"]
        )
     ],
     targets: [
        .target(
            name: "opentracing",
            path: "Pod/Classes",
            publicHeadersPath: ""
        )
     ]
 )
