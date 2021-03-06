//
//  CustomWebViewController.swift
//  Example
//
//  Created by TBD on 2017/7/28.
//  Copyright © 2017年 TBD. All rights reserved.
//

import UIKit
import TWebKit

#if swift(>=4.2)
typealias NSLayoutConstraintAttribute = NSLayoutConstraint.Attribute
#else
typealias NSLayoutConstraintAttribute = NSLayoutAttribute
#endif

class CustomWebViewController: UIViewController {
    var webView: TWebView?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.view.backgroundColor = UIColor.white
        TWebKitSetting.showAllErrorLog(false)
        let config = TWebViewConfig.init()
        config.cancelText = "取消"
        config.confirmText = "确定"
        config.progressTintColor = UIColor.orange
        config.forceOverrideCookie = false
        config.scrollChangeSizeType = .forbidden
        config.webViewCommonDelegate = TWebViewCommonDelegate.shared
        config.webViewDelegate = self
        config.failedDefaultTitle = "加载失败"
        config.loadingDefaultTitle = "加载中..."
        config.successDefaultTitle = "加载成功"
        config.progressViewHeight = 2
//        webView = TWebView.init()
        webView = TWebView.init(config: config)
//        webView = TWebView.init(frame: CGRect.init(x: 0, y: 0, width: 20, height: 20));
//        webView = TWebView.init(config: config, frame: CGRect.init(x: 0, y: 0, width: 20, height: 20))
        
        guard let webView = webView else { return }
        self.view.addSubview(webView);
        self.layoutWebView()
        if let url = URL.init(string: "http://www.qq.com/") {
            webView.load(URLRequest.init(url: url))
        }
    }
    
    func layoutWebView() {
        guard let webView = webView else { return }
        webView.translatesAutoresizingMaskIntoConstraints = false
        let array: [NSLayoutConstraintAttribute] = [.left, .right, .bottom]
        for attr in array {
            let constraint = NSLayoutConstraint.init(item: webView,
                                                     attribute: attr,
                                                     relatedBy: .equal,
                                                     toItem: self.view,
                                                     attribute: attr,
                                                     multiplier: 1.0,
                                                     constant: 0)
            self.view.addConstraint(constraint);
        }
        
        let constraint = NSLayoutConstraint.init(item: webView,
                                                 attribute: .top,
                                                 relatedBy: .equal,
                                                 toItem: self.view,
                                                 attribute: .topMargin,
                                                 multiplier: 1.0,
                                                 constant: 0)
        self.view.addConstraint(constraint);
    }
}

extension CustomWebViewController: TWebViewDelegate {
    func webView(_ webView: TWebView, loadStatus status: TWebViewLoadStatus, title: String) {
        self.navigationItem.title = title
    }
}



