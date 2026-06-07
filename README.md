# Matter-Antimatter Asymmetry at LHCb — 3rd Year Physics Lab  
  
This repo contains the code, lab report, and plots from my 8-week lab on matter-antimatter asymmetry at LHCb.  
  
The universe is composed almost entirely of matter, but the Standard Model predicts near-equal amounts of matter and antimatter should have been produced in the Big Bang. CP violation in B meson decays accounts for part of this asymmetry. In this experiment, real LHCb detector data was used to measure the global asymmetry in B⁺ and B⁻ meson decay rates, and to investigate local asymmetries across phase space using Dalitz plot analysis.  
  
In statistical terms, this project is a signal extraction and hypothesis testing pipeline: reconstructing a signal from a noisy dataset, fitting a probabilistic model to decompose signal from background, applying statistical background subtraction in 2D phase space, and testing for asymmetry using adaptive significance analysis.  
  
## Repo Structure  
  
- code — Python scripts for reconstruction and Dalitz plot analysis and systematic uncertainty estimation  
-  report — Full written report    
-  presentation — Lab presentation slides    
  
## Global Asymmetry Pipeline  
  
The raw detector data consists of momentum (3 components), energy, and charge measurements for individual particle tracks — each ideally produced by a single particle from a B meson decay.  
  
### 1. Particle Reconstruction  
  
B mesons decay into combinations of charged kaons, conserving charge. The data is structured in groups of 3 tracks. Using 4-momentum invariant mass conservation:  
  
```
m² = (ΣEᵢ)² - (Σpᵢ)²

```
  
  
the B meson mass was reconstructed for each decay, producing a mass distribution across all detected events.  
  
B mesons also decay via intermediary neutral particles (D⁰, J/ψ, φ mesons). These were identified from the invariant mass distributions of kaon pairs and removed, since b→c decays do not contribute to CP violation.  
  
### 2. Maximum Likelihood Fitting  
  
The B meson mass distribution was fit using 2 Gaussians and an exponential, implemented in Python with RooFit. Maximum likelihood fitting was used in preference to χ² minimisation — in the low-statistics regime, bin counts follow Poisson rather than Gaussian statistics, making χ² minimisation inappropriate. One Gaussian models the signal peak, one accounts for a misidentification bump from 4-body kkkπ decays, and the exponential models combinatorial background.  
  
From the fitted signal yields N⁺ and N⁻, the global asymmetry was calculated as:  
  
```
A = (N⁻ - N⁺) / (N⁻ + N⁺)

```
  
  
### 3. Yield-Purity Optimisation  
  
Each track in the dataset carries particle probabilities (prob_k, prob_pi). Rather than applying a hard kaon selection cut, the expected kaon yield was computed as the sum of prob_k values across selected tracks, with purity defined as:   
  
```
Purity = Yield / N_selected

```
  
  
By varying the prob_k threshold, the optimal cut was identified as the point of maximum distance from the linear yield-purity line— balancing data retention against sample contamination. This allowed us to use a data-driven optimisation rather than an arbitrary threshold choice.  
  
### 4. Systematic Uncertainty via Model Variation  
  
To accurately estimate systematic uncertainty in the asymmetry measurement, the fit was run across a large set of model combinations, varying the signal function (Gaussians, Crystal Ball), background model (uniform, exponential), and fitting algorithm (2D likelihood, 1D_50, yield-purity). Each combination Gabe an different estimate of A. The final result is a χ²-weighted average across all fits, with the systematic uncertainty capturing the model dependence. This approach is implemented in ==SystematicUncertainties.ipynb==.  
  
### 5. SPlot Background Subtraction  
  
To analyse local asymmetry, the intermediate particle mass distributions were plotted against each other in a 2D Dalitz plot. The raw Dalitz plot contained significant background, requiring statistical rather than hard-cut removal.  
  
SPlot is a probabilistic event decomposition technique: rather than classifying events as signal or background, every event is kept but assigned a weight based on its likelihood of belonging to the signal PDF. The technique requires the discriminating variable (B meson mass) to be uncorrelated with the Dalitz plot axes; a correlation coefficient of 0.2 was found, introducing some bias to the local asymmetry uncertainties.  
  
### 6. Parametric Bootstrapping  
  
To estimate the statistical uncertainty on the SPlot weights due to this bias, parametric bootstrapping was used. Toy datasets were repeatedly resampled from the fitted B meson mass model, SPlot applied to each resample, and the asymmetry computed. The resulting distribution of asymmetries is normally distributed (p=0.295), and gave a standard deviation describing the statistical uncertainty on the weights.  
  
### 7. Local Asymmetry and Miranda Process  
  
With background removed, local asymmetry was computed per bin using an α-corrected significance metric:  
  
```
Σ = (N⁻ - αN⁺) / √(N⁻ + α²N⁺)

```
  
  
where α = N⁻/N⁺ normalises out the global asymmetry, isolating local variation. Adaptive binning was used to ensure equal statistics per bin, placing each bin in the Gaussian limit for valid hypothesis testing.  
  
The Miranda process was then applied — testing the significance distribution against N(0,1) under the null hypothesis of no local asymmetry. A p-value of 0.09 was found, insufficient to reject H₀ at the 0.05 level, though a standard deviation of 1.131 is consistent with genuine local asymmetry. The significance Dalitz plot shows clear regions of both positive and negative asymmetry, consistent with constructive and destructive interference of strong phase differences across phase space.  
