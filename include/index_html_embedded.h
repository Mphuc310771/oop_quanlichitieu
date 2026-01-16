#ifndef INDEX_HTML_EMBEDDED_H
#define INDEX_HTML_EMBEDDED_H

inline const char *INDEX_HTML = R"RAWHTML(<!DOCTYPE html>
<html lang="vi">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Quản lý chi tiêu</title>
<link href="https://fonts.googleapis.com/css2?family=Roboto:wght@300;400;500;700&display=swap" rel="stylesheet">
<style>
* { margin: 0; padding: 0; box-sizing: border-box; }

/* Theme Variables - Vibrant Colors */
:root {
    --primary: #6366f1;
    --primary-dark: #4f46e5;
    --accent: #f472b6;
    --header-bg: linear-gradient(135deg, #6366f1 0%, #a855f7 50%, #ec4899 100%);
    --btn-primary-bg: linear-gradient(135deg, #6366f1 0%, #a855f7 100%);
    --body-bg: linear-gradient(135deg, #fdf2f8 0%, #ede9fe 50%, #dbeafe 100%);
    --card-border: rgba(99, 102, 241, 0.2);
}

[data-theme="christmas"] {
    --primary: #dc2626;
    --primary-dark: #166534;
    --accent: #fbbf24;
    --header-bg: linear-gradient(135deg, #dc2626 0%, #166534 100%);
    --btn-primary-bg: linear-gradient(135deg, #dc2626 0%, #166534 100%);
    --body-bg: linear-gradient(180deg, #0f172a 0%, #1e3a5f 100%);
    --card-border: rgba(220, 38, 38, 0.3);
}

[data-theme="tet"] {
    --primary: #dc2626;
    --primary-dark: #b91c1c;
    --accent: #fbbf24;
    --header-bg: linear-gradient(135deg, #dc2626 0%, #f97316 50%, #fbbf24 100%);
    --btn-primary-bg: linear-gradient(135deg, #dc2626 0%, #fbbf24 100%);
    --body-bg: linear-gradient(135deg, #fef2f2 0%, #fffbeb 100%);
    --card-border: rgba(220, 38, 38, 0.3);
}

body { 
    font-family: 'Roboto', sans-serif; 
    background: var(--body-bg);
    background-attachment: fixed;
    color: #202124; 
    min-height: 100vh; 
    transition: all 0.5s ease;
}

[data-theme="christmas"] body { color: #f1f5f9; }

.header {
    background: var(--header-bg);
    color: white; padding: 20px 30px;
    display: flex; justify-content: space-between; align-items: center;
    box-shadow: 0 4px 30px rgba(99, 102, 241, 0.3);
    position: relative;
    overflow: hidden;
}
.header::before {
    content: '';
    position: absolute;
    top: 0; left: 0; right: 0; bottom: 0;
    background: linear-gradient(90deg, transparent, rgba(255,255,255,0.1), transparent);
    animation: shimmer 3s infinite;
}
@keyframes shimmer { 0% { transform: translateX(-100%); } 100% { transform: translateX(100%); } }

.header h1 { font-size: 24px; font-weight: 600; display: flex; align-items: center; gap: 12px; position: relative; z-index: 1; }
.header-icon { width: 32px; height: 32px; fill: white; }
.user-info { display: flex; align-items: center; gap: 16px; position: relative; z-index: 1; }
.user-name { font-size: 14px; font-weight: 500; }
.btn-logout { background: rgba(255,255,255,0.2); border: none; color: white; padding: 10px 20px; border-radius: 25px; cursor: pointer; transition: all 0.3s; font-weight: 500; backdrop-filter: blur(10px); }
.btn-logout:hover { background: rgba(255,255,255,0.35); transform: scale(1.05); }

.theme-switcher { display: flex; gap: 8px; margin-right: 16px; }
.theme-btn { width: 38px; height: 38px; border-radius: 50%; border: 2px solid rgba(255,255,255,0.4); background: rgba(255,255,255,0.15); cursor: pointer; font-size: 18px; transition: all 0.3s; display: flex; align-items: center; justify-content: center; }
.theme-btn:hover { transform: scale(1.15) rotate(10deg); border-color: white; box-shadow: 0 0 15px rgba(255,255,255,0.5); }
.theme-btn.active { border-color: white; background: rgba(255,255,255,0.4); box-shadow: 0 0 20px rgba(255,255,255,0.6); }

.container { max-width: 1400px; margin: 0 auto; padding: 24px; }

.stats-grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(220px, 1fr)); gap: 20px; margin-bottom: 24px; }

.stat-card { 
    background: white; 
    border-radius: 20px; 
    padding: 24px; 
    box-shadow: 0 4px 20px rgba(0,0,0,0.08); 
    transition: all 0.4s cubic-bezier(0.175, 0.885, 0.32, 1.275);
    border: 2px solid transparent;
    position: relative;
    overflow: hidden;
}
.stat-card::before {
    content: '';
    position: absolute;
    top: 0; left: 0; right: 0;
    height: 4px;
    background: linear-gradient(90deg, var(--primary), var(--accent));
}
.stat-card:nth-child(1)::before { background: linear-gradient(90deg, #6366f1, #a855f7); }
.stat-card:nth-child(2)::before { background: linear-gradient(90deg, #10b981, #34d399); }
.stat-card:nth-child(3)::before { background: linear-gradient(90deg, #f59e0b, #fbbf24); }
.stat-card:nth-child(4)::before { background: linear-gradient(90deg, #ec4899, #f472b6); }

.stat-card:hover { 
    transform: translateY(-8px) scale(1.02); 
    box-shadow: 0 20px 40px rgba(99, 102, 241, 0.2);
    border-color: var(--card-border);
}
.stat-card h3 { font-size: 13px; color: #64748b; text-transform: uppercase; letter-spacing: 1px; margin-bottom: 12px; font-weight: 600; }
.stat-card .value { font-size: 32px; font-weight: 800; color: var(--primary); }
.stat-card:nth-child(1) .value { color: #6366f1; }
.stat-card:nth-child(2) .value { color: #10b981; }
.stat-card:nth-child(3) .value { color: #f59e0b; }
.stat-card:nth-child(4) .value { color: #ec4899; }

.filter-panel { background: white; border-radius: 20px; padding: 20px 24px; margin-bottom: 24px; box-shadow: 0 4px 20px rgba(0,0,0,0.06); border: 1px solid rgba(99, 102, 241, 0.1); }
.filter-header { display: flex; justify-content: space-between; align-items: center; cursor: pointer; padding: 8px 0; }
.filter-header h3 { font-size: 16px; font-weight: 600; display: flex; align-items: center; gap: 10px; color: #1e293b; }
.filter-content { display: grid; grid-template-columns: 1fr 1fr; gap: 24px; margin-top: 20px; }
@media (max-width: 800px) { .filter-content { grid-template-columns: 1fr; } }
.filter-group { margin-bottom: 16px; }
.filter-group label { display: block; font-size: 13px; color: #5f6368; margin-bottom: 8px; font-weight: 500; }
.filter-group input, .filter-group select { width: 100%; padding: 10px 14px; border: 1px solid #e0e0e0; border-radius: 10px; font-size: 14px; transition: all 0.2s; }
.filter-group input:focus, .filter-group select:focus { outline: none; border-color: var(--primary); box-shadow: 0 0 0 3px rgba(102,126,234,0.1); }
.filter-row { display: flex; gap: 12px; align-items: center; }
.filter-row input { flex: 1; }
.filter-row span { flex-shrink: 0; color: #5f6368; }
.quick-filter { display: flex; gap: 8px; flex-wrap: wrap; margin-top: 8px; }
.quick-filter button { padding: 8px 16px; border: 2px solid #e2e8f0; background: white; border-radius: 25px; font-size: 13px; cursor: pointer; transition: all 0.3s; font-weight: 500; }
.quick-filter button:hover { border-color: var(--primary); color: var(--primary); background: linear-gradient(135deg, rgba(99, 102, 241, 0.05), rgba(168, 85, 247, 0.05)); transform: translateY(-2px); }
.filter-actions { display: flex; gap: 12px; margin-top: 20px; padding-top: 20px; border-top: 1px solid #f0f0f0; }
.btn-primary { background: var(--btn-primary-bg); color: white; border: none; padding: 14px 28px; border-radius: 12px; font-size: 14px; font-weight: 600; cursor: pointer; transition: all 0.3s; box-shadow: 0 4px 15px rgba(99, 102, 241, 0.3); }
.btn-primary:hover { transform: translateY(-3px); box-shadow: 0 8px 25px rgba(99, 102, 241, 0.4); }
.btn-secondary { background: linear-gradient(135deg, #f1f5f9, #e2e8f0); color: #475569; border: none; padding: 14px 28px; border-radius: 12px; font-size: 14px; font-weight: 500; cursor: pointer; transition: all 0.3s; }
.btn-secondary:hover { background: linear-gradient(135deg, #e2e8f0, #cbd5e1); transform: translateY(-2px); }
.btn-export { background: linear-gradient(135deg, #10b981, #34d399); color: white; border: none; padding: 14px 28px; border-radius: 12px; font-size: 14px; font-weight: 600; cursor: pointer; margin-left: auto; display: flex; align-items: center; gap: 8px; box-shadow: 0 4px 15px rgba(16, 185, 129, 0.3); transition: all 0.3s; }
.btn-export:hover { transform: translateY(-3px); box-shadow: 0 8px 25px rgba(16, 185, 129, 0.4); }

.charts-grid { display: grid; grid-template-columns: 1fr 1fr; gap: 24px; margin-bottom: 24px; }
@media (max-width: 900px) { .charts-grid { grid-template-columns: 1fr; } }
.chart-card { background: white; border-radius: 20px; padding: 24px; box-shadow: 0 4px 20px rgba(0,0,0,0.06); border: 1px solid rgba(99, 102, 241, 0.1); }
.chart-card h3 { font-size: 17px; font-weight: 600; margin-bottom: 20px; display: flex; align-items: center; gap: 10px; color: var(--primary); }
.chart-container { height: 280px; display: flex; align-items: center; justify-content: center; }
.pie-chart { display: flex; align-items: center; gap: 30px; }
.pie-svg { width: 180px; height: 180px; filter: drop-shadow(0 4px 8px rgba(0,0,0,0.1)); }
.legend { display: flex; flex-direction: column; gap: 12px; }
.legend-item { display: flex; align-items: center; gap: 12px; font-size: 13px; padding: 6px 12px; border-radius: 8px; transition: all 0.2s; }
.legend-item:hover { background: #f8fafc; }
.legend-color { width: 16px; height: 16px; border-radius: 6px; box-shadow: 0 2px 4px rgba(0,0,0,0.1); }
.legend-percent { font-weight: 700; color: var(--primary); margin-left: auto; }
.bar-chart { width: 100%; height: 100%; display: flex; align-items: flex-end; justify-content: space-around; padding: 20px 0; }
.bar-item { display: flex; flex-direction: column; align-items: center; gap: 8px; }
.bar { width: 45px; background: linear-gradient(180deg, #6366f1 0%, #a855f7 50%, #ec4899 100%); border-radius: 8px 8px 0 0; transition: all 0.5s cubic-bezier(0.175, 0.885, 0.32, 1.275); box-shadow: 0 4px 15px rgba(99, 102, 241, 0.3); }
.bar:hover { transform: scaleY(1.05); }
.bar-label { font-size: 12px; color: #64748b; font-weight: 500; }
.bar-value { font-size: 12px; font-weight: 700; color: var(--primary); }

.main-content { display: grid; grid-template-columns: 1fr 1.5fr; gap: 24px; }
@media (max-width: 1000px) { .main-content { grid-template-columns: 1fr; } }
.form-section { background: white; border-radius: 20px; padding: 28px; box-shadow: 0 4px 20px rgba(0,0,0,0.06); height: fit-content; border: 1px solid rgba(99, 102, 241, 0.1); }
.form-section h2 { font-size: 20px; font-weight: 600; margin-bottom: 24px; display: flex; align-items: center; gap: 12px; color: var(--primary); }
.form-group { margin-bottom: 20px; }
.form-group label { display: block; font-size: 13px; color: #64748b; margin-bottom: 8px; font-weight: 600; text-transform: uppercase; letter-spacing: 0.5px; }
.form-group input, .form-group select { width: 100%; padding: 14px 18px; border: 2px solid #e2e8f0; border-radius: 12px; font-size: 15px; transition: all 0.3s; background: #fafbfc; }
.form-group input:focus, .form-group select:focus { outline: none; border-color: var(--primary); box-shadow: 0 0 0 4px rgba(99, 102, 241, 0.1); background: white; }
.btn-submit { width: 100%; background: var(--btn-primary-bg); color: white; border: none; padding: 16px; border-radius: 12px; font-size: 16px; font-weight: 600; cursor: pointer; transition: all 0.3s; box-shadow: 0 4px 20px rgba(99, 102, 241, 0.3); }
.btn-submit:hover { transform: translateY(-3px); box-shadow: 0 8px 30px rgba(99, 102, 241, 0.4); }

.list-section { background: white; border-radius: 20px; padding: 28px; box-shadow: 0 4px 20px rgba(0,0,0,0.06); border: 1px solid rgba(99, 102, 241, 0.1); }
.list-section h2 { font-size: 20px; font-weight: 600; margin-bottom: 20px; display: flex; align-items: center; gap: 12px; color: var(--primary); }
.expense-list { max-height: 500px; overflow-y: auto; }
.expense-item { display: flex; align-items: center; padding: 18px; border-radius: 16px; margin-bottom: 12px; background: linear-gradient(135deg, #f8fafc, #f1f5f9); transition: all 0.3s cubic-bezier(0.175, 0.885, 0.32, 1.275); border: 1px solid transparent; }
.expense-item:hover { background: linear-gradient(135deg, #ede9fe, #fce7f3); transform: translateX(8px) scale(1.01); border-color: rgba(99, 102, 241, 0.2); box-shadow: 0 4px 15px rgba(99, 102, 241, 0.1); }
.expense-info { flex: 1; }
.expense-title { font-size: 16px; font-weight: 600; color: #1e293b; margin-bottom: 6px; }
.expense-meta { font-size: 13px; color: #64748b; display: flex; gap: 15px; align-items: center; }
.expense-amount { font-size: 18px; font-weight: 700; color: #ef4444; margin-right: 20px; }
.expense-actions { display: flex; gap: 8px; }
.btn-icon { width: 36px; height: 36px; border: none; border-radius: 10px; cursor: pointer; display: flex; align-items: center; justify-content: center; transition: all 0.2s; }
.btn-edit { background: #e8f0fe; color: #667eea; }
.btn-edit:hover { background: #d2e3fc; }
.btn-delete { background: #fce8e6; color: #ea4335; }
.btn-delete:hover { background: #f5c6c0; }
.btn-icon svg { width: 18px; height: 18px; fill: currentColor; }

.category-badge { display: inline-block; padding: 4px 12px; border-radius: 20px; font-size: 12px; font-weight: 500; }
.category-food { background: #fef7e0; color: #b06000; }
.category-transport { background: #e8f0fe; color: #1a73e8; }
.category-entertainment { background: #fce8e6; color: #d93025; }
.category-shopping { background: #e6f4ea; color: #137333; }
.category-bills { background: #f3e8fd; color: #8430ce; }
.category-other { background: #f1f3f4; color: #5f6368; }

.empty-state { text-align: center; padding: 60px 20px; color: #5f6368; }
.empty-state svg { width: 80px; height: 80px; fill: #dadce0; margin-bottom: 16px; }
.empty-state p { font-size: 15px; }

/* Modal */
.modal-overlay {
    display: none; position: fixed; top: 0; left: 0; width: 100%; height: 100%;
    background: rgba(0,0,0,0.5); z-index: 1000; align-items: center; justify-content: center;
}
.modal-overlay.active { display: flex; }
.modal { background: white; border-radius: 16px; padding: 32px; width: 90%; max-width: 450px; box-shadow: 0 20px 60px rgba(0,0,0,0.3); }
.modal h2 { font-size: 20px; margin-bottom: 24px; color: #202124; }
.modal-actions { display: flex; justify-content: flex-end; gap: 12px; margin-top: 24px; }

/* Decorations */
.theme-decorations { position: fixed; top: 0; left: 0; width: 100%; height: 100%; pointer-events: none; z-index: 9999; overflow: hidden; }

/* Snow - Multiple layers for 3D effect */
.snowflake { 
    position: absolute; 
    background: white; 
    border-radius: 50%; 
    pointer-events: none;
    animation: snowfall linear infinite;
}
.snowflake.layer1 { width: 4px; height: 4px; opacity: 0.4; filter: blur(1px); }
.snowflake.layer2 { width: 6px; height: 6px; opacity: 0.7; box-shadow: 0 0 5px rgba(255,255,255,0.5); }
.snowflake.layer3 { width: 8px; height: 8px; opacity: 1; box-shadow: 0 0 10px rgba(255,255,255,0.8), 0 0 20px rgba(255,255,255,0.4); }

@keyframes snowfall { 
    0% { transform: translateY(-20px) translateX(0); opacity: 0; } 
    10% { opacity: 1; }
    100% { transform: translateY(100vh) translateX(var(--drift, 30px)); opacity: 0; } 
}

/* Yellow Apricot Blossoms for Tet */
.petal { position: absolute; animation: petalFall linear infinite; pointer-events: none; filter: drop-shadow(0 2px 3px rgba(0,0,0,0.2)); }
@keyframes petalFall { 
    0% { transform: translateY(-20px) rotate(0) scale(1); opacity: 0; } 
    10% { opacity: 1; }
    50% { transform: translateY(50vh) rotate(180deg) scale(0.9) translateX(20px); }
    100% { transform: translateY(100vh) rotate(360deg) scale(0.8) translateX(-10px); opacity: 0; } 
}

.lantern { position: fixed; font-size: 2.5rem; animation: swing 4s ease-in-out infinite, glow 2s ease-in-out infinite; opacity: 0; z-index: 100; }
[data-theme="tet"] .lantern { opacity: 1; }
@keyframes swing { 0%, 100% { transform: rotate(-8deg); } 50% { transform: rotate(8deg); } }
@keyframes glow { 0%, 100% { filter: drop-shadow(0 0 5px #fbbf24); } 50% { filter: drop-shadow(0 0 15px #f59e0b) drop-shadow(0 0 25px #dc2626); } }

/* Christmas Corner Decorations */
.christmas-corner {
    position: fixed;
    font-size: 3rem;
    z-index: 100;
    opacity: 0;
    transition: opacity 0.5s;
    filter: drop-shadow(0 4px 8px rgba(0,0,0,0.3));
}
[data-theme="christmas"] .christmas-corner { opacity: 1; }
.christmas-corner.tree-left { bottom: 20px; left: 20px; font-size: 4rem; animation: treeBounce 2s ease-in-out infinite; }
.christmas-corner.tree-right { bottom: 20px; right: 20px; font-size: 4rem; animation: treeBounce 2s ease-in-out infinite 0.5s; }
.christmas-corner.santa { top: 80px; right: 30px; font-size: 3rem; animation: santaFloat 3s ease-in-out infinite; }
.christmas-corner.gift { bottom: 20px; left: 100px; font-size: 2.5rem; animation: giftWiggle 1s ease-in-out infinite; }
@keyframes treeBounce { 0%, 100% { transform: scale(1); } 50% { transform: scale(1.05); } }
@keyframes santaFloat { 0%, 100% { transform: translateY(0); } 50% { transform: translateY(-10px); } }
@keyframes giftWiggle { 0%, 100% { transform: rotate(-5deg); } 50% { transform: rotate(5deg); } }

/* Tet Corner Decorations */
.tet-corner {
    position: fixed;
    font-size: 3rem;
    z-index: 100;
    opacity: 0;
    transition: opacity 0.5s;
    filter: drop-shadow(0 4px 8px rgba(0,0,0,0.3));
}
[data-theme="tet"] .tet-corner { opacity: 1; }
.tet-corner.banh-chung { bottom: 20px; left: 20px; font-size: 3.5rem; }
.tet-corner.dragon { bottom: 20px; right: 20px; font-size: 3.5rem; animation: dragonDance 2s ease-in-out infinite; }
.tet-corner.red-envelope { top: 80px; right: 30px; font-size: 2.5rem; animation: envelopeFloat 2s ease-in-out infinite; }
.tet-corner.firecracker { bottom: 20px; left: 100px; font-size: 2.5rem; animation: firecrackerShake 0.5s ease-in-out infinite; }
@keyframes dragonDance { 0%, 100% { transform: scaleX(1); } 50% { transform: scaleX(-1); } }
@keyframes envelopeFloat { 0%, 100% { transform: translateY(0) rotate(-5deg); } 50% { transform: translateY(-8px) rotate(5deg); } }
@keyframes firecrackerShake { 0%, 100% { transform: translateX(-2px); } 50% { transform: translateX(2px); } }
</style>
</head>
<body>

<!-- Theme Decorations -->
<div class="theme-decorations" id="themeDecorations"></div>

<!-- Christmas Decorations -->
<div class="christmas-corner tree-left">🎄</div>
<div class="christmas-corner tree-right">🎄</div>
<div class="christmas-corner santa">🎅</div>
<div class="christmas-corner gift">🎁</div>

<!-- Tet Decorations -->
<div class="lantern" style="top:100px;left:20px;">🏮</div>
<div class="lantern" style="top:140px;right:20px;">🏮</div>
<div class="tet-corner banh-chung">🍱</div>
<div class="tet-corner dragon">🐉</div>
<div class="tet-corner red-envelope">🧧</div>
<div class="tet-corner firecracker">🧨</div>

<header class="header">
    <h1>
        <svg class="header-icon" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24">
            <path d="M21 18v1c0 1.1-.9 2-2 2H5a2 2 0 01-2-2V5a2 2 0 012-2h14c1.1 0 2 .9 2 2v1h-9a2 2 0 00-2 2v8a2 2 0 002 2h9zm-9-2h10V8H12v8zm4-2.5c-.83 0-1.5-.67-1.5-1.5s.67-1.5 1.5-1.5 1.5.67 1.5 1.5-.67 1.5-1.5 1.5z"/>
        </svg>
        Quản lý chi tiêu
    </h1>
    <div class="user-info">
        <div class="theme-switcher">
            <button class="theme-btn active" onclick="setTheme('default')" title="Giao diện mặc định">🌟</button>
            <button class="theme-btn" onclick="setTheme('christmas')" title="Giao diện Giáng sinh">🎄</button>
            <button class="theme-btn" onclick="setTheme('tet')" title="Giao diện Tết">🧧</button>
        </div>
        <span class="user-name" id="currentUser">Xin chào!</span>
        <button class="btn-logout" onclick="logout()">Đăng xuất</button>
    </div>
</header>

<div class="container">
    <!-- Stats Grid -->
    <div class="stats-grid">
        <div class="stat-card"><h3>Tổng chi tiêu</h3><div class="value" id="totalExpense">0 ₫</div></div>
        <div class="stat-card"><h3>Số giao dịch</h3><div class="value" id="transactionCount">0</div></div>
        <div class="stat-card"><h3>Chi tiêu tháng này</h3><div class="value" id="monthlyExpense">0 ₫</div></div>
        <div class="stat-card"><h3>Trung bình/ngày</h3><div class="value" id="avgDaily">0 ₫</div></div>
    </div>

    <!-- Filter Panel -->
    <div class="filter-panel">
        <div class="filter-header" onclick="toggleFilter()">
            <h3>🔍 Bộ lọc nâng cao</h3>
            <span id="filterToggle">▼</span>
        </div>
        <div class="filter-content" id="filterContent">
            <div class="filter-group">
                <label>Thời gian</label>
                <div class="filter-row">
                    <input type="date" id="dateFrom">
                    <span>→</span>
                    <input type="date" id="dateTo">
                </div>
                <div class="quick-filter">
                    <button onclick="setDatePreset('today')">Hôm nay</button>
                    <button onclick="setDatePreset('7days')">7 ngày</button>
                    <button onclick="setDatePreset('month')">Tháng này</button>
                    <button onclick="setDatePreset('lastMonth')">Tháng trước</button>
                </div>
            </div>
            <div class="filter-group">
                <label>Số tiền (VND)</label>
                <div class="filter-row">
                    <input type="text" id="amountMin" placeholder="Tối thiểu" oninput="formatMoneyInput(this)">
                    <span>→</span>
                    <input type="text" id="amountMax" placeholder="Tối đa" oninput="formatMoneyInput(this)">
                </div>
                <div class="quick-filter">
                    <button onclick="setAmountPreset(0, 100000)">&lt;100k</button>
                    <button onclick="setAmountPreset(100000, 500000)">100k-500k</button>
                    <button onclick="setAmountPreset(500000, 1000000)">500k-1M</button>
                    <button onclick="setAmountPreset(1000000, null)">&gt;1M</button>
                </div>
            </div>
            <div class="filter-group">
                <label>Tìm kiếm</label>
                <input type="text" id="searchKeyword" placeholder="Nhập mô tả chi tiêu...">
            </div>
            <div class="filter-group">
                <label>Danh mục</label>
                <select id="categoryFilter">
                    <option value="">Tất cả danh mục</option>
                    <option value="food">🍔 Ăn uống</option>
                    <option value="transport">🚗 Di chuyển</option>
                    <option value="entertainment">🎬 Giải trí</option>
                    <option value="shopping">🛍️ Mua sắm</option>
                    <option value="bills">💡 Hóa đơn</option>
                    <option value="other">📦 Khác</option>
                </select>
            </div>
            <div class="filter-actions" style="grid-column: 1/-1;">
                <button class="btn-primary" onclick="applyFilters()">Áp dụng bộ lọc</button>
                <button class="btn-secondary" onclick="resetFilters()">Xóa bộ lọc</button>
                <button class="btn-export" onclick="exportCSV()">📥 Xuất CSV</button>
            </div>
        </div>
    </div>

    <!-- Charts -->
    <div class="charts-grid">
        <div class="chart-card">
            <h3>📊 Phân bổ theo danh mục</h3>
            <div class="chart-container"><div class="pie-chart" id="pieChart"></div></div>
        </div>
        <div class="chart-card">
            <h3>📈 Chi tiêu 7 ngày gần nhất</h3>
            <div class="chart-container"><div class="bar-chart" id="barChart"></div></div>
        </div>
    </div>

    <!-- Main Content -->
    <div class="main-content">
        <div class="form-section">
            <h2>➕ Thêm chi tiêu mới</h2>
            <form id="expenseForm" onsubmit="addExpense(event)">
                <div class="form-group">
                    <label>Mô tả</label>
                    <input type="text" id="title" placeholder="Nhập mô tả chi tiêu" required>
                </div>
                <div class="form-group">
                    <label>Số tiền (VND)</label>
                    <input type="text" id="amount" placeholder="Nhập số tiền" required oninput="formatMoneyInput(this)">
                </div>
                <div class="form-group">
                    <label>Danh mục</label>
                    <select id="category">
                        <option value="food">🍔 Ăn uống</option>
                        <option value="transport">🚗 Di chuyển</option>
                        <option value="entertainment">🎬 Giải trí</option>
                        <option value="shopping">🛍️ Mua sắm</option>
                        <option value="bills">💡 Hóa đơn</option>
                        <option value="other">📦 Khác</option>
                    </select>
                </div>
                <div class="form-group">
                    <label>Ngày</label>
                    <input type="date" id="date" required>
                </div>
                <button type="submit" class="btn-submit">Thêm chi tiêu</button>
            </form>
        </div>

        <div class="list-section">
            <h2>📋 Danh sách chi tiêu</h2>
            <div class="expense-list" id="expenseList"></div>
        </div>
    </div>
</div>

<!-- Edit Modal -->
<div class="modal-overlay" id="editModal">
    <div class="modal">
        <h2>✏️ Chỉnh sửa chi tiêu</h2>
        <form id="editForm" onsubmit="saveEdit(event)">
            <input type="hidden" id="editId">
            <div class="form-group"><label>Mô tả</label><input type="text" id="editTitle" required></div>
            <div class="form-group"><label>Số tiền</label><input type="text" id="editAmount" required oninput="formatMoneyInput(this)"></div>
            <div class="form-group">
                <label>Danh mục</label>
                <select id="editCategory">
                    <option value="food">🍔 Ăn uống</option>
                    <option value="transport">🚗 Di chuyển</option>
                    <option value="entertainment">🎬 Giải trí</option>
                    <option value="shopping">🛍️ Mua sắm</option>
                    <option value="bills">💡 Hóa đơn</option>
                    <option value="other">📦 Khác</option>
                </select>
            </div>
            <div class="form-group"><label>Ngày</label><input type="date" id="editDate" required></div>
            <div class="modal-actions">
                <button type="button" class="btn-secondary" onclick="closeEdit()">Hủy</button>
                <button type="submit" class="btn-primary">Lưu thay đổi</button>
            </div>
        </form>
    </div>
</div>

<script>
let allExpenses = [];
let filteredExpenses = [];
const categoryColors = { food: '#f59e0b', transport: '#3b82f6', entertainment: '#ef4444', shopping: '#10b981', bills: '#8b5cf6', other: '#6b7280' };
const categoryNames = { food: 'Ăn uống', transport: 'Di chuyển', entertainment: 'Giải trí', shopping: 'Mua sắm', bills: 'Hóa đơn', other: 'Khác' };

async function loadExpenses() {
    try {
        const res = await fetch('/api/expenses');
        allExpenses = await res.json();
        applyFilters();
    } catch(e) { console.error(e); }
}

function renderExpenses(expenses) {
    filteredExpenses = expenses;
    const list = document.getElementById('expenseList');
    if (!expenses.length) {
        list.innerHTML = '<div class="empty-state"><p>Chưa có chi tiêu nào</p></div>';
        return;
    }
    list.innerHTML = expenses.map(exp => `
        <div class="expense-item">
            <div class="expense-info">
                <div class="expense-title">${escapeHtml(exp.title)}</div>
                <div class="expense-meta">
                    <span class="category-badge category-${exp.category}">${categoryNames[exp.category] || 'Khác'}</span>
                    <span>${formatDate(exp.date)}</span>
                </div>
            </div>
            <div class="expense-amount">${formatMoney(exp.amount)}</div>
            <div class="expense-actions">
                <button class="btn-icon btn-edit" onclick="openEdit(${exp.id})">✏️</button>
                <button class="btn-icon btn-delete" onclick="deleteExpense(${exp.id})">🗑️</button>
            </div>
        </div>
    `).join('');
    updateStats(expenses);
    renderCharts(expenses);
}

function updateStats(expenses) {
    const total = expenses.reduce((sum, e) => sum + e.amount, 0);
    const now = new Date();
    const thisMonth = expenses.filter(e => { const d = new Date(e.date); return d.getMonth() === now.getMonth() && d.getFullYear() === now.getFullYear(); });
    const monthTotal = thisMonth.reduce((sum, e) => sum + e.amount, 0);
    const days = new Set(expenses.map(e => e.date)).size || 1;
    document.getElementById('totalExpense').textContent = formatMoney(total);
    document.getElementById('transactionCount').textContent = expenses.length;
    document.getElementById('monthlyExpense').textContent = formatMoney(monthTotal);
    document.getElementById('avgDaily').textContent = formatMoney(total / days);
}

function renderCharts(expenses) {
    // Pie Chart
    const cats = {};
    expenses.forEach(e => cats[e.category] = (cats[e.category] || 0) + e.amount);
    const total = Object.values(cats).reduce((a,b) => a+b, 0) || 1;
    let pieHtml = '<svg class="pie-svg" viewBox="-1 -1 2 2" style="transform:rotate(-90deg)">';
    let legendHtml = '<div class="legend">';
    let startAng = 0;
    Object.keys(cats).forEach(cat => {
        const pct = cats[cat] / total;
        const endAng = startAng + pct * Math.PI * 2;
        const x1 = Math.cos(startAng), y1 = Math.sin(startAng);
        const x2 = Math.cos(endAng), y2 = Math.sin(endAng);
        const largeArc = pct > 0.5 ? 1 : 0;
        pieHtml += `<path d="M 0 0 L ${x1} ${y1} A 1 1 0 ${largeArc} 1 ${x2} ${y2} Z" fill="${categoryColors[cat] || '#999'}"></path>`;
        legendHtml += `<div class="legend-item"><div class="legend-color" style="background:${categoryColors[cat]}"></div>${categoryNames[cat] || cat}<span class="legend-percent">${formatMoney(cats[cat])} ${(pct*100).toFixed(1)}%</span></div>`;
        startAng = endAng;
    });
    pieHtml += '</svg>';
    legendHtml += '</div>';
    document.getElementById('pieChart').innerHTML = pieHtml + legendHtml;

    // Bar Chart (7 days)
    const today = new Date();
    const days = [];
    for (let i = 6; i >= 0; i--) {
        const d = new Date(today); d.setDate(d.getDate() - i);
        const dateStr = d.toISOString().split('T')[0];
        const dayTotal = expenses.filter(e => e.date === dateStr).reduce((s, e) => s + e.amount, 0);
        days.push({ label: d.toLocaleDateString('vi-VN', {weekday: 'short'}), value: dayTotal });
    }
    const maxVal = Math.max(...days.map(d => d.value), 1);
    document.getElementById('barChart').innerHTML = days.map(d => `
        <div class="bar-item">
            <div class="bar-value">${d.value > 0 ? formatMoney(d.value) : ''}</div>
            <div class="bar" style="height:${(d.value/maxVal)*200}px"></div>
            <div class="bar-label">${d.label}</div>
        </div>
    `).join('');
}

// Filters
function toggleFilter() {
    const content = document.getElementById('filterContent');
    const toggle = document.getElementById('filterToggle');
    content.style.display = content.style.display === 'none' ? 'grid' : 'none';
    toggle.textContent = content.style.display === 'none' ? '▼' : '▲';
}

function setDatePreset(preset) {
    const today = new Date();
    let from, to;
    if (preset === 'today') { from = to = today.toISOString().split('T')[0]; }
    else if (preset === '7days') { from = new Date(today - 6*86400000).toISOString().split('T')[0]; to = today.toISOString().split('T')[0]; }
    else if (preset === 'month') { from = new Date(today.getFullYear(), today.getMonth(), 1).toISOString().split('T')[0]; to = today.toISOString().split('T')[0]; }
    else if (preset === 'lastMonth') { from = new Date(today.getFullYear(), today.getMonth()-1, 1).toISOString().split('T')[0]; to = new Date(today.getFullYear(), today.getMonth(), 0).toISOString().split('T')[0]; }
    document.getElementById('dateFrom').value = from;
    document.getElementById('dateTo').value = to;
    applyFilters();
}

function setAmountPreset(min, max) {
    document.getElementById('amountMin').value = min ? formatNumberWithDots(min) : '';
    document.getElementById('amountMax').value = max ? formatNumberWithDots(max) : '';
    applyFilters();
}

function applyFilters() {
    let filtered = [...allExpenses];
    const dateFrom = document.getElementById('dateFrom').value;
    const dateTo = document.getElementById('dateTo').value;
    const amountMinStr = document.getElementById('amountMin').value.replace(/\./g, '');
    const amountMaxStr = document.getElementById('amountMax').value.replace(/\./g, '');
    const amountMin = parseFloat(amountMinStr) || 0;
    const amountMax = parseFloat(amountMaxStr) || Infinity;
    const keyword = document.getElementById('searchKeyword').value.toLowerCase();
    const category = document.getElementById('categoryFilter').value;
    if (dateFrom) filtered = filtered.filter(e => e.date >= dateFrom);
    if (dateTo) filtered = filtered.filter(e => e.date <= dateTo);
    filtered = filtered.filter(e => e.amount >= amountMin && e.amount <= amountMax);
    if (keyword) filtered = filtered.filter(e => e.title.toLowerCase().includes(keyword));
    if (category) filtered = filtered.filter(e => e.category === category);
    renderExpenses(filtered);
}

function resetFilters() {
    document.getElementById('dateFrom').value = '';
    document.getElementById('dateTo').value = '';
    document.getElementById('amountMin').value = '';
    document.getElementById('amountMax').value = '';
    document.getElementById('searchKeyword').value = '';
    document.getElementById('categoryFilter').value = '';
    applyFilters();
}

function exportCSV() {
    let csv = 'Ngày,Mô tả,Danh mục,Số tiền\n';
    filteredExpenses.forEach(e => {
        csv += `${e.date},"${e.title}",${categoryNames[e.category] || e.category},${e.amount}\n`;
    });
    const blob = new Blob([csv], {type: 'text/csv;charset=utf-8;'});
    const link = document.createElement('a');
    link.href = URL.createObjectURL(blob);
    link.download = 'chi_tieu_' + new Date().toISOString().split('T')[0] + '.csv';
    link.click();
}

// CRUD
async function addExpense(e) {
    e.preventDefault();
    const amountStr = document.getElementById('amount').value.replace(/\./g, '');
    const data = {
        title: document.getElementById('title').value,
        amount: parseFloat(amountStr) || 0,
        category: document.getElementById('category').value,
        date: document.getElementById('date').value
    };
    await fetch('/api/expenses', { method: 'POST', headers: {'Content-Type': 'application/json'}, body: JSON.stringify(data) });
    document.getElementById('expenseForm').reset();
    document.getElementById('date').value = new Date().toISOString().split('T')[0];
    loadExpenses();
}

function openEdit(id) {
    const exp = allExpenses.find(e => e.id === id);
    if (!exp) return;
    document.getElementById('editId').value = id;
    document.getElementById('editTitle').value = exp.title;
    document.getElementById('editAmount').value = formatNumberWithDots(exp.amount);
    document.getElementById('editCategory').value = exp.category;
    document.getElementById('editDate').value = exp.date;
    document.getElementById('editModal').classList.add('active');
}

function closeEdit() { document.getElementById('editModal').classList.remove('active'); }

async function saveEdit(e) {
    e.preventDefault();
    const amountStr = document.getElementById('editAmount').value.replace(/\./g, '');
    const data = {
        id: parseInt(document.getElementById('editId').value),
        title: document.getElementById('editTitle').value,
        amount: parseFloat(amountStr) || 0,
        category: document.getElementById('editCategory').value,
        date: document.getElementById('editDate').value
    };
    await fetch('/api/expenses/' + data.id, { method: 'PUT', headers: {'Content-Type': 'application/json'}, body: JSON.stringify(data) });
    closeEdit();
    loadExpenses();
}

async function deleteExpense(id) {
    if (!confirm('Bạn có chắc muốn xóa?')) return;
    await fetch('/api/expenses/' + id, { method: 'DELETE' });
    loadExpenses();
}

async function logout() {
    await fetch('/logout', {method: 'POST'});
    window.location.href = '/login.html';
}

// Utils
function formatMoney(amount) { return formatNumberWithDots(Math.round(amount)) + ' ₫'; }
function formatNumberWithDots(num) { return Math.round(num).toString().replace(/\B(?=(\d{3})+(?!\d))/g, '.'); }
function formatMoneyInput(input) {
    let val = input.value.replace(/[^\d]/g, '');
    if (val) input.value = formatNumberWithDots(parseInt(val));
    else input.value = '';
}
function formatDate(dateStr) { return new Date(dateStr).toLocaleDateString('vi-VN'); }
function escapeHtml(text) { const div = document.createElement('div'); div.textContent = text; return div.innerHTML; }

// Theme Switcher
function setTheme(theme) {
    if (theme === 'default') {
        document.documentElement.removeAttribute('data-theme');
    } else {
        document.documentElement.setAttribute('data-theme', theme);
    }
    localStorage.setItem('theme', theme);
    document.querySelectorAll('.theme-btn').forEach(btn => btn.classList.remove('active'));
    const activeBtn = document.querySelector('.theme-btn[onclick*="' + theme + '"]');
    if (activeBtn) activeBtn.classList.add('active');
    createDecorations(theme);
}

function loadTheme() {
    const savedTheme = localStorage.getItem('theme') || 'default';
    setTheme(savedTheme);
}

function createDecorations(theme) {
    const container = document.getElementById('themeDecorations');
    container.innerHTML = '';
    
    if (theme === 'christmas') {
        // 3-layer snow for depth effect
        const layers = ['layer1', 'layer2', 'layer3'];
        const counts = [30, 25, 15]; // more small, less big
        const speeds = [[12, 8], [10, 6], [8, 4]]; // [base, random]
        
        layers.forEach((layer, idx) => {
            for (let i = 0; i < counts[idx]; i++) {
                const snow = document.createElement('div');
                snow.className = 'snowflake ' + layer;
                snow.style.left = Math.random() * 100 + '%';
                snow.style.animationDuration = (speeds[idx][0] + Math.random() * speeds[idx][1]) + 's';
                snow.style.animationDelay = '-' + Math.random() * 15 + 's';
                // Random horizontal drift
                const drift = (Math.random() - 0.5) * 60;
                snow.style.setProperty('--drift', drift + 'px');
                container.appendChild(snow);
            }
        });
    } else if (theme === 'tet') {
        // Hoa Mai Vàng Việt Nam
        const maiSymbols = ['✿', '❀', '✾'];
        for (let k = 0; k < 35; k++) {
            const petal = document.createElement('div');
            petal.className = 'petal mai-flower';
            petal.innerHTML = maiSymbols[k % 3];
            petal.style.left = Math.random() * 100 + '%';
            petal.style.animationDuration = (12 + Math.random() * 8) + 's';
            petal.style.animationDelay = '-' + Math.random() * 10 + 's';
            petal.style.fontSize = (1 + Math.random() * 0.5) + 'rem';
            petal.style.color = '#fbbf24'; // Golden yellow
            petal.style.textShadow = '0 0 5px #f59e0b, 0 2px 3px rgba(0,0,0,0.3)';
            container.appendChild(petal);
        }
    }
}

loadTheme();
document.getElementById('date').value = new Date().toISOString().split('T')[0];
loadExpenses();
</script>

</body>
</html>)RAWHTML";

#endif // INDEX_HTML_EMBEDDED_H
