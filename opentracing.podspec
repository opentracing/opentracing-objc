# GENERATED FILE: DO NOT EDIT DIRECTLY
Pod::Spec.new do |s|
  s.name             = "opentracing"
  s.version          = "0.5.1"
  s.summary          = "The OpenTracing API for Objective-C"

  s.description      = <<-DESC
                       The OpenTracing API for Objective-C, per opentracing.io.
                       DESC

  s.homepage         = "https://github.com/opentracing/opentracing-objc"
  s.license          = 'MIT'
  s.author           = { "The OpenTracing Authors" => "info@opentracing.io" }
  s.source           = { :git => "https://github.com/opentracing/opentracing-objc.git", :tag => s.version.to_s }

  s.platforms        = { :ios =>  '7.0', :watchos => '2', :osx => '10.9', :tvos => '9.0' }
  s.requires_arc = true

  s.source_files = 'Pod/Classes/**/*.{h,m}'
end
